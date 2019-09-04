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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_clk {TYPE_1__ subdev; } ;
struct gm20b_clk {int /*<<< orphan*/  base; } ;
struct gk20a_pll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPCPLL_CFG ; 
 int /*<<< orphan*/  GPCPLL_CFG_IDDQ ; 
 scalar_t__ gk20a_pllg_is_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gk20a_pllg_n_lo (int /*<<< orphan*/ *,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gk20a_pllg_read_mnp (int /*<<< orphan*/ *,struct gk20a_pll*) ; 
 struct gm20b_clk* gm20b_clk (struct nvkm_clk*) ; 
 int /*<<< orphan*/  gm20b_pllg_disable (struct gm20b_clk*) ; 
 int /*<<< orphan*/  gm20b_pllg_slide (struct gm20b_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gm20b_clk_fini(struct nvkm_clk *base)
{
	struct nvkm_device *device = base->subdev.device;
	struct gm20b_clk *clk = gm20b_clk(base);

	/* slide to VCO min */
	if (gk20a_pllg_is_enabled(&clk->base)) {
		struct gk20a_pll pll;
		u32 n_lo;

		gk20a_pllg_read_mnp(&clk->base, &pll);
		n_lo = gk20a_pllg_n_lo(&clk->base, &pll);
		gm20b_pllg_slide(clk, n_lo);
	}

	gm20b_pllg_disable(clk);

	/* set IDDQ */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_IDDQ, 1);
}