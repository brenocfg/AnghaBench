#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ br_multicast_enabled (struct net_device*) ; 
 scalar_t__ br_vlan_enabled (struct net_device*) ; 
 scalar_t__ mlxsw_sp_bridge_has_multiple_vxlans (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_vxlan_vlan_is_valid (struct net_device*) ; 

__attribute__((used)) static bool mlxsw_sp_bridge_vxlan_is_valid(struct net_device *br_dev,
					   struct netlink_ext_ack *extack)
{
	if (br_multicast_enabled(br_dev)) {
		NL_SET_ERR_MSG_MOD(extack, "Multicast can not be enabled on a bridge with a VxLAN device");
		return false;
	}

	if (!br_vlan_enabled(br_dev) &&
	    mlxsw_sp_bridge_has_multiple_vxlans(br_dev)) {
		NL_SET_ERR_MSG_MOD(extack, "Multiple VxLAN devices are not supported in a VLAN-unaware bridge");
		return false;
	}

	if (br_vlan_enabled(br_dev) &&
	    !mlxsw_sp_bridge_vxlan_vlan_is_valid(br_dev)) {
		NL_SET_ERR_MSG_MOD(extack, "Multiple VxLAN devices cannot have the same VLAN as PVID and egress untagged");
		return false;
	}

	return true;
}