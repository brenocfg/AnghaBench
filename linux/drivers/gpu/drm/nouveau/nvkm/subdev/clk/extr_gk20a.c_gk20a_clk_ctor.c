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
struct nvkm_device_tegra {int /*<<< orphan*/  clk; } ;
struct nvkm_device {TYPE_1__* func; } ;
struct nvkm_clk_func {int nr_pstates; TYPE_2__* pstates; } ;
struct gk20a_clk_pllg_params {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  subdev; } ;
struct gk20a_clk {int parent_rate; TYPE_3__ base; struct gk20a_clk_pllg_params const* params; } ;
struct TYPE_5__ {int pstate; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {struct nvkm_device_tegra* (* tegra ) (struct nvkm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int KHZ ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int nvkm_clk_ctor (struct nvkm_clk_func const*,struct nvkm_device*,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,int) ; 
 struct nvkm_device_tegra* stub1 (struct nvkm_device*) ; 

int
gk20a_clk_ctor(struct nvkm_device *device, int index,
		const struct nvkm_clk_func *func,
		const struct gk20a_clk_pllg_params *params,
		struct gk20a_clk *clk)
{
	struct nvkm_device_tegra *tdev = device->func->tegra(device);
	int ret;
	int i;

	/* Finish initializing the pstates */
	for (i = 0; i < func->nr_pstates; i++) {
		INIT_LIST_HEAD(&func->pstates[i].list);
		func->pstates[i].pstate = i + 1;
	}

	clk->params = params;
	clk->parent_rate = clk_get_rate(tdev->clk);

	ret = nvkm_clk_ctor(func, device, index, true, &clk->base);
	if (ret)
		return ret;

	nvkm_debug(&clk->base.subdev, "parent clock rate: %d Khz\n",
		   clk->parent_rate / KHZ);

	return 0;
}