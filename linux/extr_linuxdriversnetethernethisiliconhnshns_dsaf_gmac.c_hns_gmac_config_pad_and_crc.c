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
typedef  int /*<<< orphan*/  u32 ;
struct mac_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_TRANSMIT_CONTROL_REG ; 
 int /*<<< orphan*/  GMAC_TX_CRC_ADD_B ; 
 int /*<<< orphan*/  GMAC_TX_PAD_EN_B ; 
 int /*<<< orphan*/  dsaf_read_dev (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_config_pad_and_crc(void *mac_drv, u8 newval)
{
	u32 tx_ctrl;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	tx_ctrl = dsaf_read_dev(drv, GMAC_TRANSMIT_CONTROL_REG);
	dsaf_set_bit(tx_ctrl, GMAC_TX_PAD_EN_B, !!newval);
	dsaf_set_bit(tx_ctrl, GMAC_TX_CRC_ADD_B, !!newval);
	dsaf_write_dev(drv, GMAC_TRANSMIT_CONTROL_REG, tx_ctrl);
}