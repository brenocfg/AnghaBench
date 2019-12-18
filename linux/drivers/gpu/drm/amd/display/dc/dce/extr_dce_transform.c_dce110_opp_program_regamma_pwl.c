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
 int /*<<< orphan*/  program_pwl (struct dce_transform*,struct pwl_params const*) ; 
 int /*<<< orphan*/  regamma_config_regions_and_segments (struct dce_transform*,struct pwl_params const*) ; 

void dce110_opp_program_regamma_pwl(struct transform *xfm,
				    const struct pwl_params *params)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);

	/* Setup regions */
	regamma_config_regions_and_segments(xfm_dce, params);

	/* Program PWL */
	program_pwl(xfm_dce, params);
}