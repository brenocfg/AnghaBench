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
struct gk20a_pll {int dummy; } ;
struct gk20a_clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPCPLL_CFG ; 
 int /*<<< orphan*/  GPCPLL_CFG_IDDQ ; 
 struct gk20a_clk* gk20a_clk (struct nvkm_clk*) ; 
 int /*<<< orphan*/  gk20a_pllg_disable (struct gk20a_clk*) ; 
 scalar_t__ gk20a_pllg_is_enabled (struct gk20a_clk*) ; 
 int /*<<< orphan*/  gk20a_pllg_n_lo (struct gk20a_clk*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gk20a_pllg_read_mnp (struct gk20a_clk*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gk20a_pllg_slide (struct gk20a_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
gk20a_clk_fini(struct nvkm_clk *base)
{
	struct nvkm_device *device = base->subdev.device;
	struct gk20a_clk *clk = gk20a_clk(base);

	/* slide to VCO min */
	if (gk20a_pllg_is_enabled(clk)) {
		struct gk20a_pll pll;
		u32 n_lo;

		gk20a_pllg_read_mnp(clk, &pll);
		n_lo = gk20a_pllg_n_lo(clk, &pll);
		gk20a_pllg_slide(clk, n_lo);
	}

	gk20a_pllg_disable(clk);

	/* set IDDQ */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_IDDQ, 1);
}