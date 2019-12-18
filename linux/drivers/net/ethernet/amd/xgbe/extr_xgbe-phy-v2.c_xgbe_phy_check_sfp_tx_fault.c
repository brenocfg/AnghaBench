#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int* extd; } ;
struct xgbe_phy_data {int sfp_gpio_mask; int sfp_gpio_inputs; int sfp_gpio_tx_fault; TYPE_1__ sfp_eeprom; } ;

/* Variables and functions */
 int XGBE_GPIO_NO_TX_FAULT ; 
 size_t XGBE_SFP_EXTD_OPT1 ; 
 int XGBE_SFP_EXTD_OPT1_TX_FAULT ; 

__attribute__((used)) static bool xgbe_phy_check_sfp_tx_fault(struct xgbe_phy_data *phy_data)
{
	u8 *sfp_extd = phy_data->sfp_eeprom.extd;

	if (!(sfp_extd[XGBE_SFP_EXTD_OPT1] & XGBE_SFP_EXTD_OPT1_TX_FAULT))
		return false;

	if (phy_data->sfp_gpio_mask & XGBE_GPIO_NO_TX_FAULT)
		return false;

	if (phy_data->sfp_gpio_inputs & (1 << phy_data->sfp_gpio_tx_fault))
		return true;

	return false;
}