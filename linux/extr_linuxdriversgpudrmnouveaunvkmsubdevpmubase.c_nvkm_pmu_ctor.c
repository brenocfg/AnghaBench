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
struct nvkm_pmu_func {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  work; } ;
struct nvkm_pmu {TYPE_1__ recv; struct nvkm_pmu_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_pmu ; 
 int /*<<< orphan*/  nvkm_pmu_recv ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 

int
nvkm_pmu_ctor(const struct nvkm_pmu_func *func, struct nvkm_device *device,
	      int index, struct nvkm_pmu *pmu)
{
	nvkm_subdev_ctor(&nvkm_pmu, device, index, &pmu->subdev);
	pmu->func = func;
	INIT_WORK(&pmu->recv.work, nvkm_pmu_recv);
	init_waitqueue_head(&pmu->recv.wait);
	return 0;
}