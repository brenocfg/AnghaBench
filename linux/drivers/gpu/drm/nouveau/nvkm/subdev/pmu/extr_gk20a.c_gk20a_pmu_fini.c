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
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_pmu {TYPE_2__ subdev; int /*<<< orphan*/  falcon; } ;
struct gk20a_pmu {int /*<<< orphan*/  alarm; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct gk20a_pmu* gk20a_pmu (struct nvkm_pmu*) ; 
 int /*<<< orphan*/  nvkm_falcon_put (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  nvkm_timer_alarm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gk20a_pmu_fini(struct nvkm_pmu *pmu)
{
	struct gk20a_pmu *gpmu = gk20a_pmu(pmu);
	nvkm_timer_alarm(pmu->subdev.device->timer, 0, &gpmu->alarm);

	nvkm_falcon_put(pmu->falcon, &pmu->subdev);
}