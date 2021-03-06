// ------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License (MIT). See License.txt in the repo root for license information.
// ------------------------------------------------------------

#include "Common.Stdafx.h"

using namespace Reliability;

NodeDescription::NodeDescription()
    : versionInstance_(),
      nodeUpgradeDomainId_(),
      nodeFaultDomainIds_(),
      nodePropertyMap_(),
      nodeCapacityRatioMap_(),
      nodeCapacityMap_(),
      nodeName_(),
      nodeType_(),
      ipAddressOrFQDN_(),
      clusterConnectionPort_(0)
{
}

NodeDescription::NodeDescription(Federation::NodeId const& nodeId)
    : versionInstance_(),
      nodeUpgradeDomainId_(),
      nodeFaultDomainIds_(),
      nodePropertyMap_(),
      nodeCapacityRatioMap_(),
      nodeCapacityMap_(),
      nodeName_(Federation::NodeIdGenerator::GenerateNodeName(nodeId)),
      nodeType_(),
      ipAddressOrFQDN_(),
      clusterConnectionPort_(0)
{
}

NodeDescription::NodeDescription(
    Common::FabricVersionInstance const& versionInstance,
    std::wstring const& nodeUpgradeDomainId,
    std::vector<Common::Uri> const& nodeFaultDomainIds,
    std::map<std::wstring, std::wstring> const& nodePropertyMap,
    std::map<std::wstring, uint> const& nodeCapacityRatioMap,
    std::map<std::wstring, uint> const& nodeCapacityMap,
    std::wstring const& nodeName,
    std::wstring const& nodeType,
    std::wstring const& ipAddressOrFQDN,
    ULONG clusterConnectionPort)
    : versionInstance_(versionInstance),
      nodeUpgradeDomainId_(nodeUpgradeDomainId),
      nodeFaultDomainIds_(nodeFaultDomainIds),
      nodePropertyMap_(nodePropertyMap),
      nodeCapacityRatioMap_(nodeCapacityRatioMap),
      nodeCapacityMap_(nodeCapacityMap),
      nodeName_(nodeName),
      nodeType_(nodeType),
      ipAddressOrFQDN_(ipAddressOrFQDN),
      clusterConnectionPort_(clusterConnectionPort)
{
}

NodeDescription::NodeDescription(NodeDescription const& other)
    : versionInstance_(other.versionInstance_),
      nodeUpgradeDomainId_(other.nodeUpgradeDomainId_),
      nodeFaultDomainIds_(other.nodeFaultDomainIds_),
      nodePropertyMap_(other.nodePropertyMap_),
      nodeCapacityRatioMap_(other.nodeCapacityRatioMap_),
      nodeCapacityMap_(other.nodeCapacityMap_),
      nodeName_(other.nodeName_),
      nodeType_(other.nodeType_),
      ipAddressOrFQDN_(other.ipAddressOrFQDN_),
      clusterConnectionPort_(other.clusterConnectionPort_)
{
}

NodeDescription::NodeDescription(NodeDescription && other)
    : versionInstance_(std::move(other.versionInstance_)),
      nodeUpgradeDomainId_(std::move(other.nodeUpgradeDomainId_)),
      nodeFaultDomainIds_(std::move(other.nodeFaultDomainIds_)),
      nodePropertyMap_(std::move(other.nodePropertyMap_)),
      nodeCapacityRatioMap_(std::move(other.nodeCapacityRatioMap_)),
      nodeCapacityMap_(std::move(other.nodeCapacityMap_)),
      nodeName_(std::move(other.nodeName_)),
      nodeType_(std::move(other.nodeType_)),
      ipAddressOrFQDN_(std::move(other.ipAddressOrFQDN_)),
      clusterConnectionPort_(std::move(other.clusterConnectionPort_))
{
}

NodeDescription & NodeDescription::operator=(NodeDescription && other)
{
    if (this != &other)
    {
        versionInstance_ = std::move(other.versionInstance_);
        nodeUpgradeDomainId_ = std::move(other.nodeUpgradeDomainId_);
        nodeFaultDomainIds_ = std::move(other.nodeFaultDomainIds_);
        nodePropertyMap_ = std::move(other.nodePropertyMap_);
        nodeCapacityRatioMap_ = std::move(other.nodeCapacityRatioMap_);
        nodeCapacityMap_ = std::move(other.nodeCapacityMap_);
        nodeName_ = std::move(other.nodeName_);
        nodeType_ = std::move(other.nodeType_);
        ipAddressOrFQDN_ = std::move(other.ipAddressOrFQDN_);
        clusterConnectionPort_ = other.clusterConnectionPort_;
    }

    return *this;
}

void NodeDescription::InitializeNodeName(Federation::NodeId const& nodeId)
{
    if (nodeName_.size() == 0)
    {
        nodeName_ = Federation::NodeIdGenerator::GenerateNodeName(nodeId);
    }
}


void NodeDescription::WriteTo(Common::TextWriter & w, Common::FormatOptions const&) const
{
    w.WriteLine("VersionInstance: {0}", versionInstance_);

    if (!nodeUpgradeDomainId_.empty())
    {
        w.WriteLine("NodeUpgradeDomainId: {0}", nodeUpgradeDomainId_);
    }

    if (!nodeFaultDomainIds_.empty())
    {
        w.WriteLine("NodeFaultDomainIds:");
        for (Common::Uri const& nodeFaultDomainId : nodeFaultDomainIds_)
        {
            w.WriteLine(nodeFaultDomainId);
        }
    }

    if (!nodePropertyMap_.empty())
    {
        w.WriteLine("NodeProperties:");
        for (auto it = nodePropertyMap_.begin() ; it != nodePropertyMap_.end(); it++)
        {
            w.WriteLine("{0}, {1}", (*it).first, (*it).second);
        }
    }

    if (!nodeCapacityRatioMap_.empty())
    {
        w.WriteLine("NodeCapacityRatios:");
        for (auto it = nodeCapacityRatioMap_.begin() ; it != nodeCapacityRatioMap_.end(); it++)
        {
            w.WriteLine("{0}, {1}", (*it).first, (*it).second);
        }
    }

    if (!nodeCapacityMap_.empty())
    {
        w.WriteLine("NodeCapacities:");
        for (auto it = nodeCapacityMap_.begin() ; it != nodeCapacityMap_.end(); it++)
        {
            w.WriteLine("{0}, {1}", (*it).first, (*it).second);
        }
    }

    if (!nodeName_.empty())
    {
        w.WriteLine("NodeName: {0}", nodeName_);
    }

    if (!nodeType_.empty())
    {
        w.WriteLine("NodeType: {0}", nodeType_);
    }

    if (!ipAddressOrFQDN_.empty())
    {
        w.WriteLine("IpAddressOrFQDN: {0}", ipAddressOrFQDN_);
    }

    w.WriteLine("ClusterConnectionPort: {0}", clusterConnectionPort_);    
}
