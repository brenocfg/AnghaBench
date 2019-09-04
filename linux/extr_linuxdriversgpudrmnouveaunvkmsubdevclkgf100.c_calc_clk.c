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
typedef  scalar_t__ u32 ;
struct nvkm_cstate {scalar_t__* domain; } ;
struct gf100_clk_info {int coef; int ddiv; int mdiv; int ssel; scalar_t__ freq; scalar_t__ dsrc; } ;
struct gf100_clk {struct gf100_clk_info* eng; } ;

/* Variables and functions */
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__ calc_div (struct gf100_clk*,int,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ calc_pll (struct gf100_clk*,int,scalar_t__,int*) ; 
 scalar_t__ calc_src (struct gf100_clk*,int,scalar_t__,scalar_t__*,scalar_t__*) ; 
 size_t nv_clk_src_hubk06 ; 

__attribute__((used)) static int
calc_clk(struct gf100_clk *clk, struct nvkm_cstate *cstate, int idx, int dom)
{
	struct gf100_clk_info *info = &clk->eng[idx];
	u32 freq = cstate->domain[dom];
	u32 src0, div0, div1D, div1P = 0;
	u32 clk0, clk1 = 0;

	/* invalid clock domain */
	if (!freq)
		return 0;

	/* first possible path, using only dividers */
	clk0 = calc_src(clk, idx, freq, &src0, &div0);
	clk0 = calc_div(clk, idx, clk0, freq, &div1D);

	/* see if we can get any closer using PLLs */
	if (clk0 != freq && (0x00004387 & (1 << idx))) {
		if (idx <= 7)
			clk1 = calc_pll(clk, idx, freq, &info->coef);
		else
			clk1 = cstate->domain[nv_clk_src_hubk06];
		clk1 = calc_div(clk, idx, clk1, freq, &div1P);
	}

	/* select the method which gets closest to target freq */
	if (abs((int)freq - clk0) <= abs((int)freq - clk1)) {
		info->dsrc = src0;
		if (div0) {
			info->ddiv |= 0x80000000;
			info->ddiv |= div0 << 8;
			info->ddiv |= div0;
		}
		if (div1D) {
			info->mdiv |= 0x80000000;
			info->mdiv |= div1D;
		}
		info->ssel = info->coef = 0;
		info->freq = clk0;
	} else {
		if (div1P) {
			info->mdiv |= 0x80000000;
			info->mdiv |= div1P << 8;
		}
		info->ssel = (1 << idx);
		info->freq = clk1;
	}

	return 0;
}