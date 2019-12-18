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
struct nvkm_pmu {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gm20b_pmu ; 
 int nvkm_pmu_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_pmu**) ; 

int
gm20b_pmu_new(struct nvkm_device *device, int index, struct nvkm_pmu **ppmu)
{
	int ret;

	ret = nvkm_pmu_new_(&gm20b_pmu, device, index, ppmu);
	if (ret)
		return ret;

	return 0;
}