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
typedef  scalar_t__ u16 ;
typedef  struct net_device const net_device ;
struct bridge_vlan_info {int flags; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_BRENTRY ; 
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct net_device const* br_fdb_find_port (struct net_device const*,unsigned char*,scalar_t__) ; 
 scalar_t__ br_vlan_get_info (struct net_device const*,scalar_t__,struct bridge_vlan_info*) ; 
 int /*<<< orphan*/  br_vlan_get_pvid (struct net_device const*,scalar_t__*) ; 

__attribute__((used)) static struct net_device *
mlxsw_sp_span_entry_bridge_8021q(const struct net_device *br_dev,
				 unsigned char *dmac,
				 u16 *p_vid)
{
	struct bridge_vlan_info vinfo;
	struct net_device *edev;
	u16 vid = *p_vid;

	if (!vid && WARN_ON(br_vlan_get_pvid(br_dev, &vid)))
		return NULL;
	if (!vid ||
	    br_vlan_get_info(br_dev, vid, &vinfo) ||
	    !(vinfo.flags & BRIDGE_VLAN_INFO_BRENTRY))
		return NULL;

	edev = br_fdb_find_port(br_dev, dmac, vid);
	if (!edev)
		return NULL;

	if (br_vlan_get_info(edev, vid, &vinfo))
		return NULL;
	if (vinfo.flags & BRIDGE_VLAN_INFO_UNTAGGED)
		*p_vid = 0;
	else
		*p_vid = vid;
	return edev;
}