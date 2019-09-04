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
typedef  unsigned long long u64 ;
struct hw_perf_event {int /*<<< orphan*/  iommu_cntr; int /*<<< orphan*/  iommu_bank; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_PC_COUNTER_SRC_REG ; 
 int /*<<< orphan*/  amd_iommu_pc_set_reg (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 struct amd_iommu* perf_event_2_iommu (struct perf_event*) ; 

__attribute__((used)) static void perf_iommu_disable_event(struct perf_event *event)
{
	struct amd_iommu *iommu = perf_event_2_iommu(event);
	struct hw_perf_event *hwc = &event->hw;
	u64 reg = 0ULL;

	amd_iommu_pc_set_reg(iommu, hwc->iommu_bank, hwc->iommu_cntr,
			     IOMMU_PC_COUNTER_SRC_REG, &reg);
}