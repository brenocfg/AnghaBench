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
typedef  int /*<<< orphan*/  u8 ;
struct mac_driver {int /*<<< orphan*/  (* set_an_mode ) (struct mac_driver*,int /*<<< orphan*/ ) ;} ;
struct hns_mac_cb {scalar_t__ phy_if; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  stub1 (struct mac_driver*,int /*<<< orphan*/ ) ; 

int hns_mac_set_autoneg(struct hns_mac_cb *mac_cb, u8 enable)
{
	struct mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	if (mac_cb->phy_if == PHY_INTERFACE_MODE_XGMII && enable) {
		dev_err(mac_cb->dev, "enabling autoneg is not allowed!\n");
		return -ENOTSUPP;
	}

	if (mac_ctrl_drv->set_an_mode)
		mac_ctrl_drv->set_an_mode(mac_ctrl_drv, enable);

	return 0;
}