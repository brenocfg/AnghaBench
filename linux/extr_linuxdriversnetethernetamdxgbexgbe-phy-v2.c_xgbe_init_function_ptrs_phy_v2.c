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
struct xgbe_phy_impl_if {int /*<<< orphan*/  module_eeprom; int /*<<< orphan*/  module_info; int /*<<< orphan*/  kr_training_post; int /*<<< orphan*/  kr_training_pre; int /*<<< orphan*/  an_post; int /*<<< orphan*/  an_pre; int /*<<< orphan*/  an_outcome; int /*<<< orphan*/  an_advertising; int /*<<< orphan*/  an_config; int /*<<< orphan*/  an_mode; int /*<<< orphan*/  cur_mode; int /*<<< orphan*/  switch_mode; int /*<<< orphan*/  get_mode; int /*<<< orphan*/  set_mode; int /*<<< orphan*/  use_mode; int /*<<< orphan*/  valid_speed; int /*<<< orphan*/  link_status; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  reset; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; } ;
struct xgbe_phy_if {struct xgbe_phy_impl_if phy_impl; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_phy_an_advertising ; 
 int /*<<< orphan*/  xgbe_phy_an_config ; 
 int /*<<< orphan*/  xgbe_phy_an_mode ; 
 int /*<<< orphan*/  xgbe_phy_an_outcome ; 
 int /*<<< orphan*/  xgbe_phy_an_post ; 
 int /*<<< orphan*/  xgbe_phy_an_pre ; 
 int /*<<< orphan*/  xgbe_phy_cur_mode ; 
 int /*<<< orphan*/  xgbe_phy_exit ; 
 int /*<<< orphan*/  xgbe_phy_get_mode ; 
 int /*<<< orphan*/  xgbe_phy_init ; 
 int /*<<< orphan*/  xgbe_phy_kr_training_post ; 
 int /*<<< orphan*/  xgbe_phy_kr_training_pre ; 
 int /*<<< orphan*/  xgbe_phy_link_status ; 
 int /*<<< orphan*/  xgbe_phy_module_eeprom ; 
 int /*<<< orphan*/  xgbe_phy_module_info ; 
 int /*<<< orphan*/  xgbe_phy_reset ; 
 int /*<<< orphan*/  xgbe_phy_set_mode ; 
 int /*<<< orphan*/  xgbe_phy_start ; 
 int /*<<< orphan*/  xgbe_phy_stop ; 
 int /*<<< orphan*/  xgbe_phy_switch_mode ; 
 int /*<<< orphan*/  xgbe_phy_use_mode ; 
 int /*<<< orphan*/  xgbe_phy_valid_speed ; 

void xgbe_init_function_ptrs_phy_v2(struct xgbe_phy_if *phy_if)
{
	struct xgbe_phy_impl_if *phy_impl = &phy_if->phy_impl;

	phy_impl->init			= xgbe_phy_init;
	phy_impl->exit			= xgbe_phy_exit;

	phy_impl->reset			= xgbe_phy_reset;
	phy_impl->start			= xgbe_phy_start;
	phy_impl->stop			= xgbe_phy_stop;

	phy_impl->link_status		= xgbe_phy_link_status;

	phy_impl->valid_speed		= xgbe_phy_valid_speed;

	phy_impl->use_mode		= xgbe_phy_use_mode;
	phy_impl->set_mode		= xgbe_phy_set_mode;
	phy_impl->get_mode		= xgbe_phy_get_mode;
	phy_impl->switch_mode		= xgbe_phy_switch_mode;
	phy_impl->cur_mode		= xgbe_phy_cur_mode;

	phy_impl->an_mode		= xgbe_phy_an_mode;

	phy_impl->an_config		= xgbe_phy_an_config;

	phy_impl->an_advertising	= xgbe_phy_an_advertising;

	phy_impl->an_outcome		= xgbe_phy_an_outcome;

	phy_impl->an_pre		= xgbe_phy_an_pre;
	phy_impl->an_post		= xgbe_phy_an_post;

	phy_impl->kr_training_pre	= xgbe_phy_kr_training_pre;
	phy_impl->kr_training_post	= xgbe_phy_kr_training_post;

	phy_impl->module_info		= xgbe_phy_module_info;
	phy_impl->module_eeprom		= xgbe_phy_module_eeprom;
}