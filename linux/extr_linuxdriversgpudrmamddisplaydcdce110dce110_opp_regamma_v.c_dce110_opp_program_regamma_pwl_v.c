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
struct transform {int dummy; } ;
struct pwl_params {int dummy; } ;
struct dce_transform {int dummy; } ;

/* Variables and functions */
 struct dce_transform* TO_DCE_TRANSFORM (struct transform*) ; 
 int /*<<< orphan*/  configure_regamma_mode (struct dce_transform*,int) ; 
 int /*<<< orphan*/  power_on_lut (struct transform*,int,int,int) ; 
 int /*<<< orphan*/  program_pwl (struct dce_transform*,struct pwl_params const*) ; 
 int /*<<< orphan*/  regamma_config_regions_and_segments (struct dce_transform*,struct pwl_params const*) ; 
 int /*<<< orphan*/  set_bypass_input_gamma (struct dce_transform*) ; 

void dce110_opp_program_regamma_pwl_v(
	struct transform *xfm,
	const struct pwl_params *params)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);

	/* Setup regions */
	regamma_config_regions_and_segments(xfm_dce, params);

	set_bypass_input_gamma(xfm_dce);

	/* Power on gamma LUT memory */
	power_on_lut(xfm, true, false, true);

	/* Program PWL */
	program_pwl(xfm_dce, params);

	/* program regamma config */
	configure_regamma_mode(xfm_dce, 1);

	/* Power return to auto back */
	power_on_lut(xfm, false, false, true);
}