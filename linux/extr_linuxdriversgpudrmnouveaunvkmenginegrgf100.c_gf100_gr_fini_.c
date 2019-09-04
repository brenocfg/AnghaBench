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
struct nvkm_subdev {int dummy; } ;
struct nvkm_gr {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_gr {int /*<<< orphan*/  fecs; int /*<<< orphan*/  gpccs; TYPE_2__ base; } ;

/* Variables and functions */
 struct gf100_gr* gf100_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nvkm_falcon_put (int /*<<< orphan*/ ,struct nvkm_subdev*) ; 

__attribute__((used)) static int
gf100_gr_fini_(struct nvkm_gr *base, bool suspend)
{
	struct gf100_gr *gr = gf100_gr(base);
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	nvkm_falcon_put(gr->gpccs, subdev);
	nvkm_falcon_put(gr->fecs, subdev);
	return 0;
}