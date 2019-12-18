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
struct nvkm_pmu {int /*<<< orphan*/  queue; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_msgqueue_recv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
gm20b_pmu_recv(struct nvkm_pmu *pmu)
{
	if (!pmu->queue) {
		nvkm_warn(&pmu->subdev,
			  "recv function called while no firmware set!\n");
		return;
	}

	nvkm_msgqueue_recv(pmu->queue);
}