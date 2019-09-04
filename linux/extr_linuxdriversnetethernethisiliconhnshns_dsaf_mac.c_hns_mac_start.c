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
struct mac_driver {scalar_t__ mac_en_flg; int virt_dev_num; int /*<<< orphan*/  (* mac_enable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;
struct hns_mac_cb {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_COMM_MODE_RX_AND_TX ; 
 scalar_t__ MAC_EN_FLAG_V ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hns_mac_start(struct hns_mac_cb *mac_cb)
{
	struct mac_driver *mac_drv = hns_mac_get_drv(mac_cb);

	/* for virt */
	if (mac_drv->mac_en_flg == MAC_EN_FLAG_V) {
		/*plus 1 when the virtual mac has been enabled */
		mac_drv->virt_dev_num += 1;
		return;
	}

	if (mac_drv->mac_enable) {
		mac_drv->mac_enable(mac_cb->priv.mac, MAC_COMM_MODE_RX_AND_TX);
		mac_drv->mac_en_flg = MAC_EN_FLAG_V;
	}
}