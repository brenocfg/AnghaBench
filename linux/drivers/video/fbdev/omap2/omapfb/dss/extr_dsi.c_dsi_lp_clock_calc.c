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
struct dsi_lp_clock_info {unsigned int lp_clk_div; unsigned long lp_clk; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int EINVAL ; 

__attribute__((used)) static int dsi_lp_clock_calc(unsigned long dsi_fclk,
		unsigned long lp_clk_min, unsigned long lp_clk_max,
		struct dsi_lp_clock_info *lp_cinfo)
{
	unsigned lp_clk_div;
	unsigned long lp_clk;

	lp_clk_div = DIV_ROUND_UP(dsi_fclk, lp_clk_max * 2);
	lp_clk = dsi_fclk / 2 / lp_clk_div;

	if (lp_clk < lp_clk_min || lp_clk > lp_clk_max)
		return -EINVAL;

	lp_cinfo->lp_clk_div = lp_clk_div;
	lp_cinfo->lp_clk = lp_clk;

	return 0;
}