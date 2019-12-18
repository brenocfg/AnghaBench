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
struct mac_driver {int dummy; } ;
typedef  enum mac_commom_mode { ____Placeholder_mac_commom_mode } mac_commom_mode ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_XGMAC_LF_INSERT ; 
 int MAC_COMM_MODE_RX ; 
 int MAC_COMM_MODE_RX_AND_TX ; 
 int MAC_COMM_MODE_TX ; 
 int /*<<< orphan*/  hns_xgmac_lf_rf_insert (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_xgmac_rx_enable (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_xgmac_tx_enable (struct mac_driver*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_xgmac_disable(void *mac_drv, enum mac_commom_mode mode)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	if (mode == MAC_COMM_MODE_TX) {
		hns_xgmac_tx_enable(drv, 0);
	} else if (mode == MAC_COMM_MODE_RX) {
		hns_xgmac_rx_enable(drv, 0);
	} else if (mode == MAC_COMM_MODE_RX_AND_TX) {
		hns_xgmac_tx_enable(drv, 0);
		hns_xgmac_rx_enable(drv, 0);
	}
	hns_xgmac_lf_rf_insert(drv, HNS_XGMAC_LF_INSERT);
}