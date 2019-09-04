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
struct output_pixel_processor {int dummy; } ;
struct dce110_opp {int dummy; } ;
struct bit_depth_reduction_params {int dummy; } ;

/* Variables and functions */
 struct dce110_opp* TO_DCE110_OPP (struct output_pixel_processor*) ; 
 int /*<<< orphan*/  set_spatial_dither (struct dce110_opp*,struct bit_depth_reduction_params const*) ; 
 int /*<<< orphan*/  set_temporal_dither (struct dce110_opp*,struct bit_depth_reduction_params const*) ; 
 int /*<<< orphan*/  set_truncation (struct dce110_opp*,struct bit_depth_reduction_params const*) ; 

void dce110_opp_program_bit_depth_reduction(
	struct output_pixel_processor *opp,
	const struct bit_depth_reduction_params *params)
{
	struct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	set_truncation(opp110, params);
	set_spatial_dither(opp110, params);
	set_temporal_dither(opp110, params);
}