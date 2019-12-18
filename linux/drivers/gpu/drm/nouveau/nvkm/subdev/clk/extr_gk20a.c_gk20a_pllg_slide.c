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
typedef  scalar_t__ u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct gk20a_pll {scalar_t__ n; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct gk20a_clk {TYPE_1__ base; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GPCPLL_NDIV_SLOWDOWN ; 
 int /*<<< orphan*/  GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT ; 
 int /*<<< orphan*/  GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT ; 
 int /*<<< orphan*/  GPC_BCAST_NDIV_SLOWDOWN_DEBUG ; 
 int /*<<< orphan*/  GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_MASK ; 
 int /*<<< orphan*/  gk20a_pllg_read_mnp (struct gk20a_clk*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gk20a_pllg_write_mnp (struct gk20a_clk*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvkm_wait_usec (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
gk20a_pllg_slide(struct gk20a_clk *clk, u32 n)
{
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;
	struct gk20a_pll pll;
	int ret = 0;

	/* get old coefficients */
	gk20a_pllg_read_mnp(clk, &pll);
	/* do nothing if NDIV is the same */
	if (n == pll.n)
		return 0;

	/* pll slowdown mode */
	nvkm_mask(device, GPCPLL_NDIV_SLOWDOWN,
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT),
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT));

	/* new ndiv ready for ramp */
	pll.n = n;
	udelay(1);
	gk20a_pllg_write_mnp(clk, &pll);

	/* dynamic ramp to new ndiv */
	udelay(1);
	nvkm_mask(device, GPCPLL_NDIV_SLOWDOWN,
		  BIT(GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT),
		  BIT(GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT));

	/* wait for ramping to complete */
	if (nvkm_wait_usec(device, 500, GPC_BCAST_NDIV_SLOWDOWN_DEBUG,
		GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_MASK,
		GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_MASK) < 0)
		ret = -ETIMEDOUT;

	/* exit slowdown mode */
	nvkm_mask(device, GPCPLL_NDIV_SLOWDOWN,
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT) |
		BIT(GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT), 0);
	nvkm_rd32(device, GPCPLL_NDIV_SLOWDOWN);

	return ret;
}