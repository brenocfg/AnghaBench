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
struct msm_dsi_dphy_timing {int clk_prepare; int hs_rqst; int clk_zero; } ;
typedef  int s32 ;

/* Variables and functions */
 int S_DIV_ROUND_UP (int,int) ; 
 int linear_inter (int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dsi_dphy_timing_calc_clk_zero(struct msm_dsi_dphy_timing *timing,
					s32 ui, s32 coeff, s32 pcnt)
{
	s32 tmax, tmin, clk_z;
	s32 temp;

	/* reset */
	temp = 300 * coeff - ((timing->clk_prepare >> 1) + 1) * 2 * ui;
	tmin = S_DIV_ROUND_UP(temp, ui) - 2;
	if (tmin > 255) {
		tmax = 511;
		clk_z = linear_inter(2 * tmin, tmin, pcnt, 0, true);
	} else {
		tmax = 255;
		clk_z = linear_inter(tmax, tmin, pcnt, 0, true);
	}

	/* adjust */
	temp = (timing->hs_rqst + timing->clk_prepare + clk_z) & 0x7;
	timing->clk_zero = clk_z + 8 - temp;
}