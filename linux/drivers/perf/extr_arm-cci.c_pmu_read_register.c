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
typedef  int /*<<< orphan*/  u32 ;
struct cci_pmu {int /*<<< orphan*/  model; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CCI_PMU_CNTR_BASE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 pmu_read_register(struct cci_pmu *cci_pmu, int idx, unsigned int offset)
{
	return readl_relaxed(cci_pmu->base +
			     CCI_PMU_CNTR_BASE(cci_pmu->model, idx) + offset);
}