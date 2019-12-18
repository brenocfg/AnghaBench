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
struct dcn10_opp {int dummy; } ;
struct bit_depth_reduction_params {int dummy; } ;

/* Variables and functions */
 struct dcn10_opp* TO_DCN10_OPP (struct output_pixel_processor*) ; 
 int /*<<< orphan*/  opp1_set_spatial_dither (struct dcn10_opp*,struct bit_depth_reduction_params const*) ; 
 int /*<<< orphan*/  opp1_set_truncation (struct dcn10_opp*,struct bit_depth_reduction_params const*) ; 

void opp1_program_bit_depth_reduction(
	struct output_pixel_processor *opp,
	const struct bit_depth_reduction_params *params)
{
	struct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	opp1_set_truncation(oppn10, params);
	opp1_set_spatial_dither(oppn10, params);
	/* TODO
	 * set_temporal_dither(oppn10, params);
	 */
}