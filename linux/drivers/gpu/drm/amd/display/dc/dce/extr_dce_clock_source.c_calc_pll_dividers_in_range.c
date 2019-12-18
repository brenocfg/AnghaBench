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
typedef  int uint32_t ;
struct pll_settings {int adjusted_pix_clk_100hz; } ;
struct calc_pll_clock_source {int dummy; } ;

/* Variables and functions */
 int CALC_PLL_CLK_SRC_ERR_TOLERANCE ; 
 scalar_t__ calc_fb_divider_checking_tolerance (struct calc_pll_clock_source*,struct pll_settings*,int,int,int) ; 

__attribute__((used)) static bool calc_pll_dividers_in_range(
		struct calc_pll_clock_source *calc_pll_cs,
		struct pll_settings *pll_settings,
		uint32_t min_ref_divider,
		uint32_t max_ref_divider,
		uint32_t min_post_divider,
		uint32_t max_post_divider,
		uint32_t err_tolerance)
{
	uint32_t ref_divider;
	uint32_t post_divider;
	uint32_t tolerance;

/* This is err_tolerance / 10000 = 0.0025 - acceptable error of 0.25%
 * This is errorTolerance / 10000 = 0.0001 - acceptable error of 0.01%*/
	tolerance = (pll_settings->adjusted_pix_clk_100hz * err_tolerance) /
									100000;
	if (tolerance < CALC_PLL_CLK_SRC_ERR_TOLERANCE)
		tolerance = CALC_PLL_CLK_SRC_ERR_TOLERANCE;

	for (
			post_divider = max_post_divider;
			post_divider >= min_post_divider;
			--post_divider) {
		for (
				ref_divider = min_ref_divider;
				ref_divider <= max_ref_divider;
				++ref_divider) {
			if (calc_fb_divider_checking_tolerance(
					calc_pll_cs,
					pll_settings,
					ref_divider,
					post_divider,
					tolerance)) {
				return true;
			}
		}
	}

	return false;
}