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
struct nvkm_device {int dummy; } ;
struct gm20b_pll {int sdm_din; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct gm20b_clk {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPCPLL_CFG2 ; 
 int /*<<< orphan*/  GPCPLL_CFG2_SDM_DIN_MASK ; 
 int GPCPLL_CFG2_SDM_DIN_SHIFT ; 
 int /*<<< orphan*/  gk20a_pllg_write_mnp (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gm20b_pllg_write_mnp(struct gm20b_clk *clk, const struct gm20b_pll *pll)
{
	struct nvkm_device *device = clk->base.base.subdev.device;

	nvkm_mask(device, GPCPLL_CFG2, GPCPLL_CFG2_SDM_DIN_MASK,
		  pll->sdm_din << GPCPLL_CFG2_SDM_DIN_SHIFT);
	gk20a_pllg_write_mnp(&clk->base, &pll->base);
}