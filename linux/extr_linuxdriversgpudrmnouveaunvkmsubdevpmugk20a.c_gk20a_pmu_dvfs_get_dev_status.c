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
struct nvkm_falcon {int dummy; } ;
struct gk20a_pmu_dvfs_dev_status {void* total; void* busy; } ;
struct TYPE_2__ {struct nvkm_falcon* falcon; } ;
struct gk20a_pmu {TYPE_1__ base; } ;

/* Variables and functions */
 int BUSY_SLOT ; 
 int CLK_SLOT ; 
 void* nvkm_falcon_rd32 (struct nvkm_falcon*,int) ; 

__attribute__((used)) static void
gk20a_pmu_dvfs_get_dev_status(struct gk20a_pmu *pmu,
			      struct gk20a_pmu_dvfs_dev_status *status)
{
	struct nvkm_falcon *falcon = pmu->base.falcon;

	status->busy = nvkm_falcon_rd32(falcon, 0x508 + (BUSY_SLOT * 0x10));
	status->total= nvkm_falcon_rd32(falcon, 0x508 + (CLK_SLOT * 0x10));
}