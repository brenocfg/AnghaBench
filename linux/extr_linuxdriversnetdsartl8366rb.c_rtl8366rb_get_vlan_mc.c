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
typedef  scalar_t__ u32 ;
struct rtl8366_vlan_mc {scalar_t__ fid; scalar_t__ member; scalar_t__ untag; scalar_t__ priority; scalar_t__ vid; } ;
struct realtek_smi {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RTL8366RB_NUM_VLANS ; 
 scalar_t__ RTL8366RB_VLAN_FID_MASK ; 
 scalar_t__ RTL8366RB_VLAN_MC_BASE (scalar_t__) ; 
 scalar_t__ RTL8366RB_VLAN_MEMBER_MASK ; 
 scalar_t__ RTL8366RB_VLAN_PRIORITY_MASK ; 
 scalar_t__ RTL8366RB_VLAN_PRIORITY_SHIFT ; 
 scalar_t__ RTL8366RB_VLAN_UNTAG_MASK ; 
 scalar_t__ RTL8366RB_VLAN_UNTAG_SHIFT ; 
 scalar_t__ RTL8366RB_VLAN_VID_MASK ; 
 int /*<<< orphan*/  memset (struct rtl8366_vlan_mc*,char,int) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int rtl8366rb_get_vlan_mc(struct realtek_smi *smi, u32 index,
				 struct rtl8366_vlan_mc *vlanmc)
{
	u32 data[3];
	int ret;
	int i;

	memset(vlanmc, '\0', sizeof(struct rtl8366_vlan_mc));

	if (index >= RTL8366RB_NUM_VLANS)
		return -EINVAL;

	for (i = 0; i < 3; i++) {
		ret = regmap_read(smi->map,
				  RTL8366RB_VLAN_MC_BASE(index) + i,
				  &data[i]);
		if (ret)
			return ret;
	}

	vlanmc->vid = data[0] & RTL8366RB_VLAN_VID_MASK;
	vlanmc->priority = (data[0] >> RTL8366RB_VLAN_PRIORITY_SHIFT) &
		RTL8366RB_VLAN_PRIORITY_MASK;
	vlanmc->untag = (data[1] >> RTL8366RB_VLAN_UNTAG_SHIFT) &
		RTL8366RB_VLAN_UNTAG_MASK;
	vlanmc->member = data[1] & RTL8366RB_VLAN_MEMBER_MASK;
	vlanmc->fid = data[2] & RTL8366RB_VLAN_FID_MASK;

	return 0;
}