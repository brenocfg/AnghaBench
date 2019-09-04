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
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct gk20a_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GPCPLL_CFG ; 
 int /*<<< orphan*/  GPCPLL_CFG_ENABLE ; 
 int /*<<< orphan*/  GPCPLL_CFG_LOCK ; 
 int GPCPLL_CFG_LOCK_DET_OFF ; 
 int /*<<< orphan*/  SEL_VCO ; 
 int /*<<< orphan*/  SEL_VCO_GPC2CLK_OUT_SHIFT ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvkm_wait_usec (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
gk20a_pllg_enable(struct gk20a_clk *clk)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 val;

	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_ENABLE, GPCPLL_CFG_ENABLE);
	nvkm_rd32(device, GPCPLL_CFG);

	/* enable lock detection */
	val = nvkm_rd32(device, GPCPLL_CFG);
	if (val & GPCPLL_CFG_LOCK_DET_OFF) {
		val &= ~GPCPLL_CFG_LOCK_DET_OFF;
		nvkm_wr32(device, GPCPLL_CFG, val);
	}

	/* wait for lock */
	if (nvkm_wait_usec(device, 300, GPCPLL_CFG, GPCPLL_CFG_LOCK,
			   GPCPLL_CFG_LOCK) < 0)
		return -ETIMEDOUT;

	/* switch to VCO mode */
	nvkm_mask(device, SEL_VCO, BIT(SEL_VCO_GPC2CLK_OUT_SHIFT),
		BIT(SEL_VCO_GPC2CLK_OUT_SHIFT));

	return 0;
}