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
struct pwl_params {int /*<<< orphan*/  hw_points_num; int /*<<< orphan*/  rgb_resulted; } ;
struct dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpp1_degamma_ram_select (struct dpp*,int) ; 
 int /*<<< orphan*/  dpp1_power_on_degamma_lut (struct dpp*,int) ; 
 int /*<<< orphan*/  dpp1_program_degamma_luta_settings (struct dpp*,struct pwl_params const*) ; 
 int /*<<< orphan*/  dpp1_program_degamma_lutb_settings (struct dpp*,struct pwl_params const*) ; 
 int /*<<< orphan*/  dpp2_degamma_ram_inuse (struct dpp*,int*) ; 
 int /*<<< orphan*/  dpp2_enable_cm_block (struct dpp*) ; 
 int /*<<< orphan*/  dpp2_program_degamma_lut (struct dpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void dpp2_set_degamma_pwl(
		struct dpp *dpp_base,
		const struct pwl_params *params)
{
	bool is_ram_a = true;

	dpp1_power_on_degamma_lut(dpp_base, true);
	dpp2_enable_cm_block(dpp_base);
	dpp2_degamma_ram_inuse(dpp_base, &is_ram_a);
	if (is_ram_a == true)
		dpp1_program_degamma_lutb_settings(dpp_base, params);
	else
		dpp1_program_degamma_luta_settings(dpp_base, params);

	dpp2_program_degamma_lut(dpp_base, params->rgb_resulted, params->hw_points_num, !is_ram_a);
	dpp1_degamma_ram_select(dpp_base, !is_ram_a);
}