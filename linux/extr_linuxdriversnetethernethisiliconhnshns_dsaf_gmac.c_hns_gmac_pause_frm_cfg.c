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
 int /*<<< orphan*/  GMAC_PAUSE_EN_REG ; 
 int /*<<< orphan*/  GMAC_PAUSE_EN_RX_FDFC_B ; 
 int /*<<< orphan*/  GMAC_PAUSE_EN_TX_FDFC_B ; 
 int /*<<< orphan*/  dsaf_read_dev (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_pause_frm_cfg(void *mac_drv, u32 rx_pause_en,
				   u32 tx_pause_en)
{
	u32 pause_en;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	pause_en = dsaf_read_dev(drv, GMAC_PAUSE_EN_REG);
	dsaf_set_bit(pause_en, GMAC_PAUSE_EN_RX_FDFC_B, !!rx_pause_en);
	dsaf_set_bit(pause_en, GMAC_PAUSE_EN_TX_FDFC_B, !!tx_pause_en);
	dsaf_write_dev(drv, GMAC_PAUSE_EN_REG, pause_en);
}