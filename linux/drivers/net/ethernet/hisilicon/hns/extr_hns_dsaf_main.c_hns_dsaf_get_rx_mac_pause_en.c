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
typedef  int u32 ;
struct dsaf_device {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSAF_MAC_PAUSE_RX_EN_B ; 
 scalar_t__ DSAF_PAUSE_CFG_REG ; 
 int dsaf_get_dev_bit (struct dsaf_device*,scalar_t__,int /*<<< orphan*/ ) ; 

void hns_dsaf_get_rx_mac_pause_en(struct dsaf_device *dsaf_dev, int mac_id,
				  u32 *en)
{
	if (AE_IS_VER1(dsaf_dev->dsaf_ver))
		*en = 1;
	else
		*en = dsaf_get_dev_bit(dsaf_dev,
				       DSAF_PAUSE_CFG_REG + mac_id * 4,
				       DSAF_MAC_PAUSE_RX_EN_B);
}