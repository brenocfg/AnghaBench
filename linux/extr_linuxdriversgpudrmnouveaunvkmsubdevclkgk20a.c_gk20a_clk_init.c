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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct nvkm_clk {TYPE_2__* func; } ;
struct TYPE_6__ {struct nvkm_subdev subdev; } ;
struct gk20a_clk {TYPE_3__ base; } ;
struct TYPE_5__ {int (* prog ) (TYPE_3__*) ;TYPE_1__* pstates; int /*<<< orphan*/  (* calc ) (struct nvkm_clk*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPC2CLK_OUT ; 
 int /*<<< orphan*/  GPC2CLK_OUT_INIT_MASK ; 
 int /*<<< orphan*/  GPC2CLK_OUT_INIT_VAL ; 
 int /*<<< orphan*/  GPCPLL_CFG ; 
 int /*<<< orphan*/  GPCPLL_CFG_IDDQ ; 
 struct gk20a_clk* gk20a_clk (struct nvkm_clk*) ; 
 int gk20a_clk_setup_slide (struct gk20a_clk*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_clk*,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
gk20a_clk_init(struct nvkm_clk *base)
{
	struct gk20a_clk *clk = gk20a_clk(base);
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;
	int ret;

	/* get out from IDDQ */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_IDDQ, 0);
	nvkm_rd32(device, GPCPLL_CFG);
	udelay(5);

	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_INIT_MASK,
		  GPC2CLK_OUT_INIT_VAL);

	ret = gk20a_clk_setup_slide(clk);
	if (ret)
		return ret;

	/* Start with lowest frequency */
	base->func->calc(base, &base->func->pstates[0].base);
	ret = base->func->prog(&clk->base);
	if (ret) {
		nvkm_error(subdev, "cannot initialize clock\n");
		return ret;
	}

	return 0;
}