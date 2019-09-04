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
struct nvkm_device {int /*<<< orphan*/  cfgopt; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ucode; } ;
struct gf100_gr_func {TYPE_1__ fecs; } ;
struct gf100_gr {int /*<<< orphan*/  base; scalar_t__ firmware; struct gf100_gr_func const* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_gr_ ; 
 scalar_t__ nvkm_boolopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int nvkm_gr_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ *) ; 

int
gf100_gr_ctor(const struct gf100_gr_func *func, struct nvkm_device *device,
	      int index, struct gf100_gr *gr)
{
	gr->func = func;
	gr->firmware = nvkm_boolopt(device->cfgopt, "NvGrUseFW",
				    func->fecs.ucode == NULL);

	return nvkm_gr_ctor(&gf100_gr_, device, index,
			    gr->firmware || func->fecs.ucode != NULL,
			    &gr->base);
}