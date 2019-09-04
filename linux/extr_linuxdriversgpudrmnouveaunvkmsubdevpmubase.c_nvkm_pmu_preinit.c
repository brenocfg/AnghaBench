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
struct nvkm_subdev {int dummy; } ;
struct nvkm_pmu {int dummy; } ;

/* Variables and functions */
 struct nvkm_pmu* nvkm_pmu (struct nvkm_subdev*) ; 
 int nvkm_pmu_reset (struct nvkm_pmu*) ; 

__attribute__((used)) static int
nvkm_pmu_preinit(struct nvkm_subdev *subdev)
{
	struct nvkm_pmu *pmu = nvkm_pmu(subdev);
	return nvkm_pmu_reset(pmu);
}