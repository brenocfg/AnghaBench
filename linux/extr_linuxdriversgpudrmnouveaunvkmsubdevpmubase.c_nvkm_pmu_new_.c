#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvkm_pmu_func {int dummy; } ;
struct nvkm_pmu {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_pmu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_pmu_ctor (struct nvkm_pmu_func const*,struct nvkm_device*,int,struct nvkm_pmu*) ; 

int
nvkm_pmu_new_(const struct nvkm_pmu_func *func, struct nvkm_device *device,
	      int index, struct nvkm_pmu **ppmu)
{
	struct nvkm_pmu *pmu;
	if (!(pmu = *ppmu = kzalloc(sizeof(*pmu), GFP_KERNEL)))
		return -ENOMEM;
	return nvkm_pmu_ctor(func, device, index, *ppmu);
}