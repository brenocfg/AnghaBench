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
struct switchdev_obj_port_vlan {int /*<<< orphan*/  vid_end; int /*<<< orphan*/  vid_begin; } ;
struct realtek_smi {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct dsa_switch {struct realtek_smi* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* is_vlan_valid ) (struct realtek_smi*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtl8366_enable_vlan4k (struct realtek_smi*,int) ; 
 int /*<<< orphan*/  stub1 (struct realtek_smi*,int) ; 

int rtl8366_vlan_prepare(struct dsa_switch *ds, int port,
			 const struct switchdev_obj_port_vlan *vlan)
{
	struct realtek_smi *smi = ds->priv;
	int ret;

	if (!smi->ops->is_vlan_valid(smi, port))
		return -EINVAL;

	dev_info(smi->dev, "prepare VLANs %04x..%04x\n",
		 vlan->vid_begin, vlan->vid_end);

	/* Enable VLAN in the hardware
	 * FIXME: what's with this 4k business?
	 * Just rtl8366_enable_vlan() seems inconclusive.
	 */
	ret = rtl8366_enable_vlan4k(smi, true);
	if (ret)
		return ret;

	return 0;
}