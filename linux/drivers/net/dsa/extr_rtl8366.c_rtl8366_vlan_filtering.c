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
struct rtl8366_vlan_4k {int /*<<< orphan*/  untag; int /*<<< orphan*/  member; } ;
struct realtek_smi {TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct realtek_smi* priv; } ;
struct TYPE_2__ {int (* get_vlan_4k ) (struct realtek_smi*,int,struct rtl8366_vlan_4k*) ;int /*<<< orphan*/  (* is_vlan_valid ) (struct realtek_smi*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,int) ; 
 int rtl8366_set_vlan (struct realtek_smi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct realtek_smi*,int) ; 
 int stub2 (struct realtek_smi*,int,struct rtl8366_vlan_4k*) ; 

int rtl8366_vlan_filtering(struct dsa_switch *ds, int port, bool vlan_filtering)
{
	struct realtek_smi *smi = ds->priv;
	struct rtl8366_vlan_4k vlan4k;
	int ret;

	/* Use VLAN nr port + 1 since VLAN0 is not valid */
	if (!smi->ops->is_vlan_valid(smi, port + 1))
		return -EINVAL;

	dev_info(smi->dev, "%s filtering on port %d\n",
		 vlan_filtering ? "enable" : "disable",
		 port);

	/* TODO:
	 * The hardware support filter ID (FID) 0..7, I have no clue how to
	 * support this in the driver when the callback only says on/off.
	 */
	ret = smi->ops->get_vlan_4k(smi, port + 1, &vlan4k);
	if (ret)
		return ret;

	/* Just set the filter to FID 1 for now then */
	ret = rtl8366_set_vlan(smi, port + 1,
			       vlan4k.member,
			       vlan4k.untag,
			       1);
	if (ret)
		return ret;

	return 0;
}