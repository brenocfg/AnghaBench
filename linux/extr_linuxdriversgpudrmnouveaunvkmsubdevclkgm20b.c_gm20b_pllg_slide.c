#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ n; } ;
struct gm20b_pll {scalar_t__ sdm_din; TYPE_3__ base; } ;
struct TYPE_4__ {struct nvkm_subdev subdev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct gm20b_clk {TYPE_2__ base; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GPCPLL_CFG2 ; 
 scalar_t__ GPCPLL_CFG2_SDM_DIN_MASK ; 
 scalar_t__ GPCPLL_CFG2_SDM_DIN_NEW_MASK ; 
 scalar_t__ GPCPLL_CFG2_SDM_DIN_NEW_SHIFT ; 
 scalar_t__ GPCPLL_CFG2_SDM_DIN_SHIFT ; 
 int /*<<< orphan*/  GPCPLL_NDIV_SLOWDOWN ; 
 int /*<<< orphan*/  GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT ; 
 int /*<<< orphan*/  GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT ; 
 int /*<<< orphan*/  GPC_BCAST_NDIV_SLOWDOWN_DEBUG ; 
 int /*<<< orphan*/  GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_MASK ; 
 int /*<<< orphan*/  gk20a_pllg_write_mnp (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gm20b_dvfs_calc_ndiv (struct gm20b_clk*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gm20b_pllg_read_mnp (struct gm20b_clk*,struct gm20b_pll*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvkm_wait_usec (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
gm20b_pllg_slide(struct gm20b_clk *clk, u32 n)
{
	struct nvkm_subdev *subdev = &clk->base.base.subdev;
	struct nvkm_device *device = subdev->device;
	struct gm20b_pll pll;
	u32 n_int, sdm_din;
	int ret = 0;

	/* calculate the new n_int/sdm_din for this n/uv */
	gm20b_dvfs_calc_ndiv(clk, n, &n_int, &sdm_din);

	/* get old coefficients */
	gm20b_pllg_read_mnp(clk, &pll);
	/* do nothing if NDIV is the same */
	if (n_int == pll.base.n && sdm_din == pll.sdm_din)
		return 0;

	/* pll slowdown mode */
	nvkm_mask(device, GPCPLL_NDIV_SLOWDOWN,
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT),
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT));

	/* new ndiv ready for ramp */
	/* in DVFS mode SDM is updated via "new" field */
	nvkm_mask(device, GPCPLL_CFG2, GPCPLL_CFG2_SDM_DIN_NEW_MASK,
		  sdm_din << GPCPLL_CFG2_SDM_DIN_NEW_SHIFT);
	pll.base.n = n_int;
	udelay(1);
	gk20a_pllg_write_mnp(&clk->base, &pll.base);

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

	/* in DVFS mode complete SDM update */
	nvkm_mask(device, GPCPLL_CFG2, GPCPLL_CFG2_SDM_DIN_MASK,
		  sdm_din << GPCPLL_CFG2_SDM_DIN_SHIFT);

	/* exit slowdown mode */
	nvkm_mask(device, GPCPLL_NDIV_SLOWDOWN,
		BIT(GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT) |
		BIT(GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT), 0);
	nvkm_rd32(device, GPCPLL_NDIV_SLOWDOWN);

	return ret;
}