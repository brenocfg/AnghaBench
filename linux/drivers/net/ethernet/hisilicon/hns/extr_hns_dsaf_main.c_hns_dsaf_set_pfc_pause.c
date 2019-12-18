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
struct dsaf_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 scalar_t__ DSAF_PAUSE_CFG_REG ; 
 int /*<<< orphan*/  DSAF_PFC_PAUSE_RX_EN_B ; 
 int /*<<< orphan*/  DSAF_PFC_PAUSE_TX_EN_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct dsaf_device*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_dsaf_set_pfc_pause(struct dsaf_device *dsaf_dev,
				   int mac_id, int tx_en, int rx_en)
{
	if (AE_IS_VER1(dsaf_dev->dsaf_ver)) {
		if (!tx_en || !rx_en)
			dev_err(dsaf_dev->dev, "dsaf v1 can not close pfc!\n");

		return;
	}

	dsaf_set_dev_bit(dsaf_dev, DSAF_PAUSE_CFG_REG + mac_id * 4,
			 DSAF_PFC_PAUSE_RX_EN_B, !!rx_en);
	dsaf_set_dev_bit(dsaf_dev, DSAF_PAUSE_CFG_REG + mac_id * 4,
			 DSAF_PFC_PAUSE_TX_EN_B, !!tx_en);
}