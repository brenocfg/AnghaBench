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
struct realtek_smi {int vlan_enabled; int vlan4k_enabled; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable_vlan ) (struct realtek_smi*,int) ;int (* enable_vlan4k ) (struct realtek_smi*,int) ;} ;

/* Variables and functions */
 int stub1 (struct realtek_smi*,int) ; 
 int stub2 (struct realtek_smi*,int) ; 

int rtl8366_enable_vlan(struct realtek_smi *smi, bool enable)
{
	int ret;

	ret = smi->ops->enable_vlan(smi, enable);
	if (ret)
		return ret;

	smi->vlan_enabled = enable;

	/* If we turn VLAN off, make sure that we turn off
	 * 4k VLAN as well, if that happened to be on.
	 */
	if (!enable) {
		smi->vlan4k_enabled = false;
		ret = smi->ops->enable_vlan4k(smi, false);
	}

	return ret;
}