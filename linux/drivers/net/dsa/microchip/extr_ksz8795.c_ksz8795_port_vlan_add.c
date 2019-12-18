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
typedef  int u8 ;
typedef  int u16 ;
struct switchdev_obj_port_vlan {int flags; int vid_begin; int vid_end; } ;
struct ksz_device {int dummy; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BRIDGE_VLAN_INFO_PVID ; 
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 int /*<<< orphan*/  PORT_REMOVE_TAG ; 
 int /*<<< orphan*/  P_TAG_CTRL ; 
 int /*<<< orphan*/  REG_PORT_CTRL_VID ; 
 int /*<<< orphan*/  ksz8795_from_vlan (int,int*,int*,int*) ; 
 int /*<<< orphan*/  ksz8795_r_vlan_table (struct ksz_device*,int,int*) ; 
 int /*<<< orphan*/  ksz8795_to_vlan (int,int,int,int*) ; 
 int /*<<< orphan*/  ksz8795_w_vlan_table (struct ksz_device*,int,int) ; 
 int /*<<< orphan*/  ksz_port_cfg (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_pread16 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_pwrite16 (struct ksz_device*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ksz8795_port_vlan_add(struct dsa_switch *ds, int port,
				  const struct switchdev_obj_port_vlan *vlan)
{
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	struct ksz_device *dev = ds->priv;
	u16 data, vid, new_pvid = 0;
	u8 fid, member, valid;

	ksz_port_cfg(dev, port, P_TAG_CTRL, PORT_REMOVE_TAG, untagged);

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		ksz8795_r_vlan_table(dev, vid, &data);
		ksz8795_from_vlan(data, &fid, &member, &valid);

		/* First time to setup the VLAN entry. */
		if (!valid) {
			/* Need to find a way to map VID to FID. */
			fid = 1;
			valid = 1;
		}
		member |= BIT(port);

		ksz8795_to_vlan(fid, member, valid, &data);
		ksz8795_w_vlan_table(dev, vid, data);

		/* change PVID */
		if (vlan->flags & BRIDGE_VLAN_INFO_PVID)
			new_pvid = vid;
	}

	if (new_pvid) {
		ksz_pread16(dev, port, REG_PORT_CTRL_VID, &vid);
		vid &= 0xfff;
		vid |= new_pvid;
		ksz_pwrite16(dev, port, REG_PORT_CTRL_VID, vid);
	}
}