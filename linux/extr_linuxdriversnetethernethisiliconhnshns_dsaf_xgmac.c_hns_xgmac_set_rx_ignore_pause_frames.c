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
 int /*<<< orphan*/  XGMAC_MAC_PAUSE_CTRL_REG ; 
 int /*<<< orphan*/  XGMAC_PAUSE_CTL_RX_B ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_xgmac_set_rx_ignore_pause_frames(void *mac_drv, u32 enable)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, XGMAC_MAC_PAUSE_CTRL_REG,
			 XGMAC_PAUSE_CTL_RX_B, !!enable);
}