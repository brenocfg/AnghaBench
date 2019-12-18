#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int m; int n; } ;
union aty_pll {TYPE_1__ ibm514; } ;
typedef  int u8 ;
typedef  int u32 ;
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {int ref_clk_per; } ;

/* Variables and functions */

__attribute__((used)) static u32 aty_pll_514_to_var(const struct fb_info *info,
			      const union aty_pll *pll)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u8 df, vco_div_count, ref_div_count;

	df = pll->ibm514.m >> 6;
	vco_div_count = pll->ibm514.m & 0x3f;
	ref_div_count = pll->ibm514.n;

	return ((par->ref_clk_per * ref_div_count) << (3 - df))/
	    		(vco_div_count + 65);
}