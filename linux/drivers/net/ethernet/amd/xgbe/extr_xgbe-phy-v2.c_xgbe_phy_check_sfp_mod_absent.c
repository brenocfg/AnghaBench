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
struct xgbe_phy_data {int sfp_gpio_mask; int sfp_gpio_inputs; int sfp_gpio_mod_absent; } ;

/* Variables and functions */
 int XGBE_GPIO_NO_MOD_ABSENT ; 

__attribute__((used)) static bool xgbe_phy_check_sfp_mod_absent(struct xgbe_phy_data *phy_data)
{
	if (phy_data->sfp_gpio_mask & XGBE_GPIO_NO_MOD_ABSENT)
		return false;

	if (phy_data->sfp_gpio_inputs & (1 << phy_data->sfp_gpio_mod_absent))
		return true;

	return false;
}