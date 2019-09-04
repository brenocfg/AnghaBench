#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_subdev {int dummy; } ;
struct TYPE_8__ {struct nvkm_subdev subdev; } ;
struct nvkm_gr {TYPE_2__ engine; } ;
struct TYPE_10__ {TYPE_3__* device; } ;
struct TYPE_11__ {TYPE_4__ subdev; } ;
struct TYPE_12__ {TYPE_5__ engine; } ;
struct gf100_gr {TYPE_1__* func; int /*<<< orphan*/  gpccs; int /*<<< orphan*/  fecs; TYPE_6__ base; } ;
struct TYPE_9__ {int /*<<< orphan*/  pmu; } ;
struct TYPE_7__ {int (* init ) (struct gf100_gr*) ;} ;

/* Variables and functions */
 struct gf100_gr* gf100_gr (struct nvkm_gr*) ; 
 int nvkm_falcon_get (int /*<<< orphan*/ ,struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_pmu_pgob (int /*<<< orphan*/ ,int) ; 
 int stub1 (struct gf100_gr*) ; 

__attribute__((used)) static int
gf100_gr_init_(struct nvkm_gr *base)
{
	struct gf100_gr *gr = gf100_gr(base);
	struct nvkm_subdev *subdev = &base->engine.subdev;
	u32 ret;

	nvkm_pmu_pgob(gr->base.engine.subdev.device->pmu, false);

	ret = nvkm_falcon_get(gr->fecs, subdev);
	if (ret)
		return ret;

	ret = nvkm_falcon_get(gr->gpccs, subdev);
	if (ret)
		return ret;

	return gr->func->init(gr);
}