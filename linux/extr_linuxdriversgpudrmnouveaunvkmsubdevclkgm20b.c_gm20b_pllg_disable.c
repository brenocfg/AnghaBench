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
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct gm20b_clk {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPCPLL_CFG ; 
 int /*<<< orphan*/  GPCPLL_CFG_ENABLE ; 
 int /*<<< orphan*/  GPCPLL_CFG_SYNC_MODE ; 
 int /*<<< orphan*/  SEL_VCO ; 
 int /*<<< orphan*/  SEL_VCO_GPC2CLK_OUT_SHIFT ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gm20b_pllg_disable(struct gm20b_clk *clk)
{
	struct nvkm_device *device = clk->base.base.subdev.device;

	/* put PLL in bypass before disabling it */
	nvkm_mask(device, SEL_VCO, BIT(SEL_VCO_GPC2CLK_OUT_SHIFT), 0);

	/* clear SYNC_MODE before disabling PLL */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_SYNC_MODE, 0);

	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_ENABLE, 0);
	nvkm_rd32(device, GPCPLL_CFG);
}