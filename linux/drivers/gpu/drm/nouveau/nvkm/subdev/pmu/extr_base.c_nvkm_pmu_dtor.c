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
struct nvkm_pmu {int /*<<< orphan*/  falcon; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_falcon_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_msgqueue_del (int /*<<< orphan*/ *) ; 
 void* nvkm_pmu (struct nvkm_subdev*) ; 

__attribute__((used)) static void *
nvkm_pmu_dtor(struct nvkm_subdev *subdev)
{
	struct nvkm_pmu *pmu = nvkm_pmu(subdev);
	nvkm_msgqueue_del(&pmu->queue);
	nvkm_falcon_del(&pmu->falcon);
	return nvkm_pmu(subdev);
}