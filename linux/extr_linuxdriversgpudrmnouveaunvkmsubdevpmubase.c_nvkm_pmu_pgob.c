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
struct nvkm_pmu {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pgob ) (struct nvkm_pmu*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_pmu*,int) ; 

void
nvkm_pmu_pgob(struct nvkm_pmu *pmu, bool enable)
{
	if (pmu && pmu->func->pgob)
		pmu->func->pgob(pmu, enable);
}