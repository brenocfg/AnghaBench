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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nvkm_pmu {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_SUBDEV_PMU ; 
 int nvkm_mc_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
gf100_pmu_enabled(struct nvkm_pmu *pmu)
{
	return nvkm_mc_enabled(pmu->subdev.device, NVKM_SUBDEV_PMU);
}