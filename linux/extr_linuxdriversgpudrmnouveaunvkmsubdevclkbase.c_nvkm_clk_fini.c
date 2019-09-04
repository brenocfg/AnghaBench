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
struct nvkm_subdev {int dummy; } ;
struct nvkm_clk {TYPE_1__* func; int /*<<< orphan*/  work; int /*<<< orphan*/  pwrsrc_ntfy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct nvkm_clk*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct nvkm_clk* nvkm_clk (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_notify_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_clk*) ; 

__attribute__((used)) static int
nvkm_clk_fini(struct nvkm_subdev *subdev, bool suspend)
{
	struct nvkm_clk *clk = nvkm_clk(subdev);
	nvkm_notify_put(&clk->pwrsrc_ntfy);
	flush_work(&clk->work);
	if (clk->func->fini)
		clk->func->fini(clk);
	return 0;
}