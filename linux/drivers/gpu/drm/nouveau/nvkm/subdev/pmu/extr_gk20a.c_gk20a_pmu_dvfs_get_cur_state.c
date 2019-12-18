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
struct nvkm_clk {int pstate; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ subdev; } ;
struct gk20a_pmu {TYPE_3__ base; } ;
struct TYPE_4__ {struct nvkm_clk* clk; } ;

/* Variables and functions */

__attribute__((used)) static void
gk20a_pmu_dvfs_get_cur_state(struct gk20a_pmu *pmu, int *state)
{
	struct nvkm_clk *clk = pmu->base.subdev.device->clk;

	*state = clk->pstate;
}