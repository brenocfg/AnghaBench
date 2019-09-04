#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct switchdev_obj_port_vlan {scalar_t__ vid_begin; scalar_t__ vid_end; } ;
struct rtl8366_vlan_mc {scalar_t__ vid; scalar_t__ fid; scalar_t__ untag; scalar_t__ member; scalar_t__ priority; } ;
struct realtek_smi {int num_vlan_mc; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct dsa_switch {struct realtek_smi* priv; } ;
struct TYPE_2__ {int (* get_vlan_mc ) (struct realtek_smi*,int,struct rtl8366_vlan_mc*) ;int (* set_vlan_mc ) (struct realtek_smi*,int,struct rtl8366_vlan_mc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int stub1 (struct realtek_smi*,int,struct rtl8366_vlan_mc*) ; 
 int stub2 (struct realtek_smi*,int,struct rtl8366_vlan_mc*) ; 

int rtl8366_vlan_del(struct dsa_switch *ds, int port,
		     const struct switchdev_obj_port_vlan *vlan)
{
	struct realtek_smi *smi = ds->priv;
	u16 vid;
	int ret;

	dev_info(smi->dev, "del VLAN on port %d\n", port);

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; ++vid) {
		int i;

		dev_info(smi->dev, "del VLAN %04x\n", vid);

		for (i = 0; i < smi->num_vlan_mc; i++) {
			struct rtl8366_vlan_mc vlanmc;

			ret = smi->ops->get_vlan_mc(smi, i, &vlanmc);
			if (ret)
				return ret;

			if (vid == vlanmc.vid) {
				/* clear VLAN member configurations */
				vlanmc.vid = 0;
				vlanmc.priority = 0;
				vlanmc.member = 0;
				vlanmc.untag = 0;
				vlanmc.fid = 0;

				ret = smi->ops->set_vlan_mc(smi, i, &vlanmc);
				if (ret) {
					dev_err(smi->dev,
						"failed to remove VLAN %04x\n",
						vid);
					return ret;
				}
				break;
			}
		}
	}

	return 0;
}