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
struct mac_driver {int (* need_adjust_link ) (struct mac_driver*,int,int) ;} ;
struct TYPE_2__ {scalar_t__ mac; } ;
struct hns_mac_cb {TYPE_1__ priv; } ;
typedef  enum mac_speed { ____Placeholder_mac_speed } mac_speed ;

/* Variables and functions */
 int stub1 (struct mac_driver*,int,int) ; 

bool hns_mac_need_adjust_link(struct hns_mac_cb *mac_cb, int speed, int duplex)
{
	struct mac_driver *mac_ctrl_drv;

	mac_ctrl_drv = (struct mac_driver *)(mac_cb->priv.mac);

	if (mac_ctrl_drv->need_adjust_link)
		return mac_ctrl_drv->need_adjust_link(mac_ctrl_drv,
			(enum mac_speed)speed, duplex);
	else
		return true;
}