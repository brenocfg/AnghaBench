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
struct TYPE_2__ {struct nvkm_falcon* falcon; } ;
struct gk20a_pmu {TYPE_1__ base; } ;

/* Variables and functions */
 int BUSY_SLOT ; 
 int CLK_SLOT ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 

__attribute__((used)) static void
gk20a_pmu_dvfs_reset_dev_status(struct gk20a_pmu *pmu)
{
	struct nvkm_falcon *falcon = pmu->base.falcon;

	nvkm_falcon_wr32(falcon, 0x508 + (BUSY_SLOT * 0x10), 0x80000000);
	nvkm_falcon_wr32(falcon, 0x508 + (CLK_SLOT * 0x10), 0x80000000);
}