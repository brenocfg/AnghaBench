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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct pll_settings {scalar_t__ adjusted_pix_clk_100hz; int reference_freq; scalar_t__ vco_freq; scalar_t__ calculated_pix_clk_100hz; scalar_t__ pix_clk_post_divider; scalar_t__ fract_feedback_divider; scalar_t__ feedback_divider; scalar_t__ reference_divider; } ;
struct calc_pll_clock_source {int fract_fb_divider_factor; int ref_freq_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  calculate_fb_and_fractional_fb_divider (struct calc_pll_clock_source*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int div_u64 (int,scalar_t__) ; 

__attribute__((used)) static bool calc_fb_divider_checking_tolerance(
		struct calc_pll_clock_source *calc_pll_cs,
		struct pll_settings *pll_settings,
		uint32_t ref_divider,
		uint32_t post_divider,
		uint32_t tolerance)
{
	uint32_t feedback_divider;
	uint32_t fract_feedback_divider;
	uint32_t actual_calculated_clock_100hz;
	uint32_t abs_err;
	uint64_t actual_calc_clk_100hz;

	calculate_fb_and_fractional_fb_divider(
			calc_pll_cs,
			pll_settings->adjusted_pix_clk_100hz,
			ref_divider,
			post_divider,
			&feedback_divider,
			&fract_feedback_divider);

	/*Actual calculated value*/
	actual_calc_clk_100hz = (uint64_t)feedback_divider *
					calc_pll_cs->fract_fb_divider_factor +
							fract_feedback_divider;
	actual_calc_clk_100hz *= calc_pll_cs->ref_freq_khz * 10;
	actual_calc_clk_100hz =
		div_u64(actual_calc_clk_100hz,
			ref_divider * post_divider *
				calc_pll_cs->fract_fb_divider_factor);

	actual_calculated_clock_100hz = (uint32_t)(actual_calc_clk_100hz);

	abs_err = (actual_calculated_clock_100hz >
					pll_settings->adjusted_pix_clk_100hz)
			? actual_calculated_clock_100hz -
					pll_settings->adjusted_pix_clk_100hz
			: pll_settings->adjusted_pix_clk_100hz -
						actual_calculated_clock_100hz;

	if (abs_err <= tolerance) {
		/*found good values*/
		pll_settings->reference_freq = calc_pll_cs->ref_freq_khz;
		pll_settings->reference_divider = ref_divider;
		pll_settings->feedback_divider = feedback_divider;
		pll_settings->fract_feedback_divider = fract_feedback_divider;
		pll_settings->pix_clk_post_divider = post_divider;
		pll_settings->calculated_pix_clk_100hz =
			actual_calculated_clock_100hz;
		pll_settings->vco_freq =
			actual_calculated_clock_100hz * post_divider / 10;
		return true;
	}
	return false;
}