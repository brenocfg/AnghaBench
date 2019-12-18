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
 int /*<<< orphan*/  XGMAC_RF_TX_EN_B ; 
 int /*<<< orphan*/  XGMAC_UNIDIR_EN_B ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_xgmac_lf_rf_control_init(struct mac_driver *mac_drv)
{
	u32 val = 0;

	dsaf_set_bit(val, XGMAC_UNIDIR_EN_B, 0);
	dsaf_set_bit(val, XGMAC_RF_TX_EN_B, 1);
	dsaf_set_field(val, XGMAC_LF_RF_INSERT_M, XGMAC_LF_RF_INSERT_S, 0);
	dsaf_write_dev(mac_drv, XGMAC_MAC_TX_LF_RF_CONTROL_REG, val);
}