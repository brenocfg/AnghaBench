#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct gk20a_pll {scalar_t__ n; scalar_t__ m; scalar_t__ pl; } ;
struct gm20b_pll {scalar_t__ sdm_din; struct gk20a_pll base; } ;
struct TYPE_4__ {struct nvkm_subdev subdev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct gm20b_clk {TYPE_2__ base; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 int /*<<< orphan*/  GPC2CLK_OUT ; 
 int GPC2CLK_OUT_VCODIV1 ; 
 int GPC2CLK_OUT_VCODIV2 ; 
 int /*<<< orphan*/  GPC2CLK_OUT_VCODIV_MASK ; 
 int GPC2CLK_OUT_VCODIV_SHIFT ; 
 scalar_t__ ffs (scalar_t__) ; 
 int /*<<< orphan*/  gk20a_pllg_is_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  gk20a_pllg_write_mnp (TYPE_2__*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gm20b_dvfs_calc_ndiv (struct gm20b_clk*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gm20b_pllg_disable (struct gm20b_clk*) ; 
 int gm20b_pllg_enable (struct gm20b_clk*) ; 
 int /*<<< orphan*/  gm20b_pllg_read_mnp (struct gm20b_clk*,struct gm20b_pll*) ; 
 int /*<<< orphan*/  gm20b_pllg_write_mnp (struct gm20b_clk*,struct gm20b_pll*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
gm20b_pllg_program_mnp(struct gm20b_clk *clk, const struct gk20a_pll *pll)
{
	struct nvkm_subdev *subdev = &clk->base.base.subdev;
	struct nvkm_device *device = subdev->device;
	struct gm20b_pll cur_pll;
	u32 n_int, sdm_din;
	/* if we only change pdiv, we can do a glitchless transition */
	bool pdiv_only;
	int ret;

	gm20b_dvfs_calc_ndiv(clk, pll->n, &n_int, &sdm_din);
	gm20b_pllg_read_mnp(clk, &cur_pll);
	pdiv_only = cur_pll.base.n == n_int && cur_pll.sdm_din == sdm_din &&
		    cur_pll.base.m == pll->m;

	/* need full sequence if clock not enabled yet */
	if (!gk20a_pllg_is_enabled(&clk->base))
		pdiv_only = false;

	/* split VCO-to-bypass jump in half by setting out divider 1:2 */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV2 << GPC2CLK_OUT_VCODIV_SHIFT);
	/* Intentional 2nd write to assure linear divider operation */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV2 << GPC2CLK_OUT_VCODIV_SHIFT);
	nvkm_rd32(device, GPC2CLK_OUT);
	udelay(2);

	if (pdiv_only) {
		u32 old = cur_pll.base.pl;
		u32 new = pll->pl;

		/*
		 * we can do a glitchless transition only if the old and new PL
		 * parameters share at least one bit set to 1. If this is not
		 * the case, calculate and program an interim PL that will allow
		 * us to respect that rule.
		 */
		if ((old & new) == 0) {
			cur_pll.base.pl = min(old | BIT(ffs(new) - 1),
					      new | BIT(ffs(old) - 1));
			gk20a_pllg_write_mnp(&clk->base, &cur_pll.base);
		}

		cur_pll.base.pl = new;
		gk20a_pllg_write_mnp(&clk->base, &cur_pll.base);
	} else {
		/* disable before programming if more than pdiv changes */
		gm20b_pllg_disable(clk);

		cur_pll.base = *pll;
		cur_pll.base.n = n_int;
		cur_pll.sdm_din = sdm_din;
		gm20b_pllg_write_mnp(clk, &cur_pll);

		ret = gm20b_pllg_enable(clk);
		if (ret)
			return ret;
	}

	/* restore out divider 1:1 */
	udelay(2);
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV1 << GPC2CLK_OUT_VCODIV_SHIFT);
	/* Intentional 2nd write to assure linear divider operation */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV1 << GPC2CLK_OUT_VCODIV_SHIFT);
	nvkm_rd32(device, GPC2CLK_OUT);

	return 0;
}