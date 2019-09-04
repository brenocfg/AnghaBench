#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mac_driver {scalar_t__ virt_dev_num; scalar_t__ mac_en_flg; int /*<<< orphan*/  (* mac_disable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  mac; } ;
struct hns_mac_cb {TYPE_3__* dsaf_dev; scalar_t__ link; TYPE_1__ priv; } ;
struct TYPE_6__ {TYPE_2__* misc_op; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cpld_reset_led ) (struct hns_mac_cb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_COMM_MODE_RX_AND_TX ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct hns_mac_cb*) ; 

void hns_mac_stop(struct hns_mac_cb *mac_cb)
{
	struct mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	/*modified for virtualization */
	if (mac_ctrl_drv->virt_dev_num > 0) {
		mac_ctrl_drv->virt_dev_num -= 1;
		if (mac_ctrl_drv->virt_dev_num > 0)
			return;
	}

	if (mac_ctrl_drv->mac_disable)
		mac_ctrl_drv->mac_disable(mac_cb->priv.mac,
			MAC_COMM_MODE_RX_AND_TX);

	mac_ctrl_drv->mac_en_flg = 0;
	mac_cb->link = 0;
	mac_cb->dsaf_dev->misc_op->cpld_reset_led(mac_cb);
}