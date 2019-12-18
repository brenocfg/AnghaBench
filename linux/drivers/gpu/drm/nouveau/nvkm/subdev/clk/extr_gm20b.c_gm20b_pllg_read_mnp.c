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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct gm20b_pll {int sdm_din; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct gm20b_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPCPLL_CFG2 ; 
 int GPCPLL_CFG2_SDM_DIN_SHIFT ; 
 int /*<<< orphan*/  GPCPLL_CFG2_SDM_DIN_WIDTH ; 
 int MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gk20a_pllg_read_mnp (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gm20b_pllg_read_mnp(struct gm20b_clk *clk, struct gm20b_pll *pll)
{
	struct nvkm_subdev *subdev = &clk->base.base.subdev;
	struct nvkm_device *device = subdev->device;
	u32 val;

	gk20a_pllg_read_mnp(&clk->base, &pll->base);
	val = nvkm_rd32(device, GPCPLL_CFG2);
	pll->sdm_din = (val >> GPCPLL_CFG2_SDM_DIN_SHIFT) &
		       MASK(GPCPLL_CFG2_SDM_DIN_WIDTH);
}