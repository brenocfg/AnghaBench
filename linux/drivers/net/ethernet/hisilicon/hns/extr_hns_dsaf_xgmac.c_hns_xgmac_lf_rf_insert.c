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
typedef  int /*<<< orphan*/  u32 ;
struct mac_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGMAC_LF_RF_INSERT_M ; 
 int /*<<< orphan*/  XGMAC_LF_RF_INSERT_S ; 
 int /*<<< orphan*/  XGMAC_MAC_TX_LF_RF_CONTROL_REG ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_xgmac_lf_rf_insert(struct mac_driver *mac_drv, u32 mode)
{
	dsaf_set_dev_field(mac_drv, XGMAC_MAC_TX_LF_RF_CONTROL_REG,
			   XGMAC_LF_RF_INSERT_M, XGMAC_LF_RF_INSERT_S, mode);
}