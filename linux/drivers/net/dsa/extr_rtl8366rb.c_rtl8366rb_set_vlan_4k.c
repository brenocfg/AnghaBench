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
typedef  int u32 ;
struct rtl8366_vlan_4k {int vid; int member; int untag; int fid; } ;
struct realtek_smi {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTL8366RB_FIDMAX ; 
 int RTL8366RB_NUM_VIDS ; 
 scalar_t__ RTL8366RB_TABLE_ACCESS_CTRL_REG ; 
 int RTL8366RB_TABLE_VLAN_WRITE_CTRL ; 
 int RTL8366RB_VLAN_FID_MASK ; 
 int RTL8366RB_VLAN_MEMBER_MASK ; 
 scalar_t__ RTL8366RB_VLAN_TABLE_WRITE_BASE ; 
 int RTL8366RB_VLAN_UNTAG_MASK ; 
 int RTL8366RB_VLAN_UNTAG_SHIFT ; 
 int RTL8366RB_VLAN_VID_MASK ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int rtl8366rb_set_vlan_4k(struct realtek_smi *smi,
				 const struct rtl8366_vlan_4k *vlan4k)
{
	u32 data[3];
	int ret;
	int i;

	if (vlan4k->vid >= RTL8366RB_NUM_VIDS ||
	    vlan4k->member > RTL8366RB_VLAN_MEMBER_MASK ||
	    vlan4k->untag > RTL8366RB_VLAN_UNTAG_MASK ||
	    vlan4k->fid > RTL8366RB_FIDMAX)
		return -EINVAL;

	data[0] = vlan4k->vid & RTL8366RB_VLAN_VID_MASK;
	data[1] = (vlan4k->member & RTL8366RB_VLAN_MEMBER_MASK) |
		  ((vlan4k->untag & RTL8366RB_VLAN_UNTAG_MASK) <<
			RTL8366RB_VLAN_UNTAG_SHIFT);
	data[2] = vlan4k->fid & RTL8366RB_VLAN_FID_MASK;

	for (i = 0; i < 3; i++) {
		ret = regmap_write(smi->map,
				   RTL8366RB_VLAN_TABLE_WRITE_BASE + i,
				   data[i]);
		if (ret)
			return ret;
	}

	/* write table access control word */
	ret = regmap_write(smi->map, RTL8366RB_TABLE_ACCESS_CTRL_REG,
			   RTL8366RB_TABLE_VLAN_WRITE_CTRL);

	return ret;
}