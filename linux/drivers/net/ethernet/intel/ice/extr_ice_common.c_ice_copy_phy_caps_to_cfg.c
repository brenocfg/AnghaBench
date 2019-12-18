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
struct ice_aqc_set_phy_cfg_data {int /*<<< orphan*/  link_fec_opt; int /*<<< orphan*/  eeer_value; int /*<<< orphan*/  eee_cap; int /*<<< orphan*/  low_power_ctrl; int /*<<< orphan*/  caps; int /*<<< orphan*/  phy_type_high; int /*<<< orphan*/  phy_type_low; } ;
struct ice_aqc_get_phy_caps_data {int /*<<< orphan*/  link_fec_options; int /*<<< orphan*/  eeer_value; int /*<<< orphan*/  eee_cap; int /*<<< orphan*/  low_power_ctrl; int /*<<< orphan*/  caps; int /*<<< orphan*/  phy_type_high; int /*<<< orphan*/  phy_type_low; } ;

/* Variables and functions */

void
ice_copy_phy_caps_to_cfg(struct ice_aqc_get_phy_caps_data *caps,
			 struct ice_aqc_set_phy_cfg_data *cfg)
{
	if (!caps || !cfg)
		return;

	cfg->phy_type_low = caps->phy_type_low;
	cfg->phy_type_high = caps->phy_type_high;
	cfg->caps = caps->caps;
	cfg->low_power_ctrl = caps->low_power_ctrl;
	cfg->eee_cap = caps->eee_cap;
	cfg->eeer_value = caps->eeer_value;
	cfg->link_fec_opt = caps->link_fec_options;
}