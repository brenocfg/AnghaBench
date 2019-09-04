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
typedef  scalar_t__ u32 ;
struct mac_driver {int /*<<< orphan*/  (* mac_pausefrm_cfg ) (struct mac_driver*,scalar_t__,scalar_t__) ;} ;
struct hns_mac_cb {scalar_t__ mac_type; int /*<<< orphan*/  dev; TYPE_1__* dsaf_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ HNAE_PORT_DEBUG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  stub1 (struct mac_driver*,scalar_t__,scalar_t__) ; 

int hns_mac_set_pauseparam(struct hns_mac_cb *mac_cb, u32 rx_en, u32 tx_en)
{
	struct mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);
	bool is_ver1 = AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver);

	if (mac_cb->mac_type == HNAE_PORT_DEBUG) {
		if (is_ver1 && (tx_en || rx_en)) {
			dev_err(mac_cb->dev, "macv1 can't enable tx/rx_pause!\n");
			return -EINVAL;
		}
	}

	if (mac_ctrl_drv->mac_pausefrm_cfg)
		mac_ctrl_drv->mac_pausefrm_cfg(mac_ctrl_drv, rx_en, tx_en);

	return 0;
}