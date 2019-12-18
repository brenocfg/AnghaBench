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
struct xgbe_phy_if {int /*<<< orphan*/  module_eeprom; int /*<<< orphan*/  module_info; int /*<<< orphan*/  an_isr; int /*<<< orphan*/  phy_valid_speed; int /*<<< orphan*/  phy_config_aneg; int /*<<< orphan*/  phy_status; int /*<<< orphan*/  phy_stop; int /*<<< orphan*/  phy_start; int /*<<< orphan*/  phy_reset; int /*<<< orphan*/  phy_exit; int /*<<< orphan*/  phy_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_an_combined_isr ; 
 int /*<<< orphan*/  xgbe_phy_config_aneg ; 
 int /*<<< orphan*/  xgbe_phy_exit ; 
 int /*<<< orphan*/  xgbe_phy_init ; 
 int /*<<< orphan*/  xgbe_phy_module_eeprom ; 
 int /*<<< orphan*/  xgbe_phy_module_info ; 
 int /*<<< orphan*/  xgbe_phy_reset ; 
 int /*<<< orphan*/  xgbe_phy_start ; 
 int /*<<< orphan*/  xgbe_phy_status ; 
 int /*<<< orphan*/  xgbe_phy_stop ; 
 int /*<<< orphan*/  xgbe_phy_valid_speed ; 

void xgbe_init_function_ptrs_phy(struct xgbe_phy_if *phy_if)
{
	phy_if->phy_init        = xgbe_phy_init;
	phy_if->phy_exit        = xgbe_phy_exit;

	phy_if->phy_reset       = xgbe_phy_reset;
	phy_if->phy_start       = xgbe_phy_start;
	phy_if->phy_stop        = xgbe_phy_stop;

	phy_if->phy_status      = xgbe_phy_status;
	phy_if->phy_config_aneg = xgbe_phy_config_aneg;

	phy_if->phy_valid_speed = xgbe_phy_valid_speed;

	phy_if->an_isr          = xgbe_an_combined_isr;

	phy_if->module_info     = xgbe_phy_module_info;
	phy_if->module_eeprom   = xgbe_phy_module_eeprom;
}