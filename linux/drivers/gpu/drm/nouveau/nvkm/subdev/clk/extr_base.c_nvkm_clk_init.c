#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {int dummy; } ;
struct nvkm_domain {size_t name; } ;
struct TYPE_5__ {int* domain; } ;
struct TYPE_7__ {int pstate; TYPE_1__ base; int /*<<< orphan*/  list; } ;
struct nvkm_clk {int pstate; int temp; scalar_t__ dstate; scalar_t__ state_nr; scalar_t__ astate; TYPE_2__* func; TYPE_3__ bstate; struct nvkm_domain* domains; } ;
struct TYPE_6__ {int (* init ) (struct nvkm_clk*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 size_t nv_clk_src_max ; 
 struct nvkm_clk* nvkm_clk (struct nvkm_subdev*) ; 
 int nvkm_clk_read (struct nvkm_clk*,size_t) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,size_t) ; 
 int /*<<< orphan*/  nvkm_pstate_calc (struct nvkm_clk*,int) ; 
 int /*<<< orphan*/  nvkm_pstate_info (struct nvkm_clk*,TYPE_3__*) ; 
 int stub1 (struct nvkm_clk*) ; 

__attribute__((used)) static int
nvkm_clk_init(struct nvkm_subdev *subdev)
{
	struct nvkm_clk *clk = nvkm_clk(subdev);
	const struct nvkm_domain *clock = clk->domains;
	int ret;

	memset(&clk->bstate, 0x00, sizeof(clk->bstate));
	INIT_LIST_HEAD(&clk->bstate.list);
	clk->bstate.pstate = 0xff;

	while (clock->name != nv_clk_src_max) {
		ret = nvkm_clk_read(clk, clock->name);
		if (ret < 0) {
			nvkm_error(subdev, "%02x freq unknown\n", clock->name);
			return ret;
		}
		clk->bstate.base.domain[clock->name] = ret;
		clock++;
	}

	nvkm_pstate_info(clk, &clk->bstate);

	if (clk->func->init)
		return clk->func->init(clk);

	clk->astate = clk->state_nr - 1;
	clk->dstate = 0;
	clk->pstate = -1;
	clk->temp = 90; /* reasonable default value */
	nvkm_pstate_calc(clk, true);
	return 0;
}