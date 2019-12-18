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
struct TYPE_2__ {int /*<<< orphan*/  pmu_counters_mask; } ;
struct arm_ccn {TYPE_1__ dt; } ;

/* Variables and functions */
 scalar_t__ CCN_NUM_PMU_EVENT_COUNTERS ; 
 int bitmap_weight (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int arm_ccn_pmu_active_counters(struct arm_ccn *ccn)
{
	return bitmap_weight(ccn->dt.pmu_counters_mask,
			     CCN_NUM_PMU_EVENT_COUNTERS + 1);
}