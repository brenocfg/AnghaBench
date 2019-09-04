#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nvkm_clk {int dummy; } ;
struct gk20a_pll {int dummy; } ;
struct TYPE_3__ {struct gk20a_pll pll; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dfs_coeff; int /*<<< orphan*/  dfs_ext_cal; } ;
struct gm20b_clk {scalar_t__ uv; scalar_t__ new_uv; scalar_t__ safe_fmax_vmin; TYPE_1__ base; struct gk20a_pll new_pll; TYPE_2__ new_dvfs; TYPE_2__ dvfs; } ;

/* Variables and functions */
 struct gm20b_clk* gm20b_clk (struct nvkm_clk*) ; 
 int /*<<< orphan*/  gm20b_dvfs_calc_safe_pll (struct gm20b_clk*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gm20b_dvfs_program_coeff (struct gm20b_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gm20b_dvfs_program_dfs_detection (struct gm20b_clk*,TYPE_2__*) ; 
 int /*<<< orphan*/  gm20b_dvfs_program_ext_cal (struct gm20b_clk*,int /*<<< orphan*/ ) ; 
 int gm20b_pllg_program_mnp_slide (struct gm20b_clk*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  nv_clk_src_gpc ; 
 scalar_t__ nvkm_clk_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gm20b_clk_prog(struct nvkm_clk *base)
{
	struct gm20b_clk *clk = gm20b_clk(base);
	u32 cur_freq;
	int ret;

	/* No change in DVFS settings? */
	if (clk->uv == clk->new_uv)
		goto prog;

	/*
	 * Interim step for changing DVFS detection settings: low enough
	 * frequency to be safe at at DVFS coeff = 0.
	 *
	 * 1. If voltage is increasing:
	 * - safe frequency target matches the lowest - old - frequency
	 * - DVFS settings are still old
	 * - Voltage already increased to new level by volt, but maximum
	 *   detection limit assures PLL output remains under F/V curve
	 *
	 * 2. If voltage is decreasing:
	 * - safe frequency target matches the lowest - new - frequency
	 * - DVFS settings are still old
	 * - Voltage is also old, it will be lowered by volt afterwards
	 *
	 * Interim step can be skipped if old frequency is below safe minimum,
	 * i.e., it is low enough to be safe at any voltage in operating range
	 * with zero DVFS coefficient.
	 */
	cur_freq = nvkm_clk_read(&clk->base.base, nv_clk_src_gpc);
	if (cur_freq > clk->safe_fmax_vmin) {
		struct gk20a_pll pll_safe;

		if (clk->uv < clk->new_uv)
			/* voltage will raise: safe frequency is current one */
			pll_safe = clk->base.pll;
		else
			/* voltage will drop: safe frequency is new one */
			pll_safe = clk->new_pll;

		gm20b_dvfs_calc_safe_pll(clk, &pll_safe);
		ret = gm20b_pllg_program_mnp_slide(clk, &pll_safe);
		if (ret)
			return ret;
	}

	/*
	 * DVFS detection settings transition:
	 * - Set DVFS coefficient zero
	 * - Set calibration level to new voltage
	 * - Set DVFS coefficient to match new voltage
	 */
	gm20b_dvfs_program_coeff(clk, 0);
	gm20b_dvfs_program_ext_cal(clk, clk->new_dvfs.dfs_ext_cal);
	gm20b_dvfs_program_coeff(clk, clk->new_dvfs.dfs_coeff);
	gm20b_dvfs_program_dfs_detection(clk, &clk->new_dvfs);

prog:
	clk->uv = clk->new_uv;
	clk->dvfs = clk->new_dvfs;
	clk->base.pll = clk->new_pll;

	return gm20b_pllg_program_mnp_slide(clk, &clk->base.pll);
}