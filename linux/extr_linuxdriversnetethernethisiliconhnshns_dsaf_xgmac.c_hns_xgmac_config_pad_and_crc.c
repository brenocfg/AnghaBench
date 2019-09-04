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
 int /*<<< orphan*/  XGMAC_CTL_RX_FCS_B ; 
 int /*<<< orphan*/  XGMAC_CTL_TX_FCS_B ; 
 int /*<<< orphan*/  XGMAC_CTL_TX_PAD_B ; 
 int /*<<< orphan*/  XGMAC_MAC_CONTROL_REG ; 
 int /*<<< orphan*/  dsaf_read_dev (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_xgmac_config_pad_and_crc(void *mac_drv, u8 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	u32 origin = dsaf_read_dev(drv, XGMAC_MAC_CONTROL_REG);

	dsaf_set_bit(origin, XGMAC_CTL_TX_PAD_B, !!newval);
	dsaf_set_bit(origin, XGMAC_CTL_TX_FCS_B, !!newval);
	dsaf_set_bit(origin, XGMAC_CTL_RX_FCS_B, !!newval);
	dsaf_write_dev(drv, XGMAC_MAC_CONTROL_REG, origin);
}