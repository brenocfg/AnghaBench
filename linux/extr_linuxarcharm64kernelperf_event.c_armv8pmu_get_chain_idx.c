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
struct pmu_hw_events {int /*<<< orphan*/  used_mask; } ;
struct arm_pmu {int num_events; } ;

/* Variables and functions */
 int ARMV8_IDX_COUNTER0 ; 
 int EAGAIN ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armv8pmu_get_chain_idx(struct pmu_hw_events *cpuc,
				   struct arm_pmu *cpu_pmu)
{
	int idx;

	/*
	 * Chaining requires two consecutive event counters, where
	 * the lower idx must be even.
	 */
	for (idx = ARMV8_IDX_COUNTER0 + 1; idx < cpu_pmu->num_events; idx += 2) {
		if (!test_and_set_bit(idx, cpuc->used_mask)) {
			/* Check if the preceding even counter is available */
			if (!test_and_set_bit(idx - 1, cpuc->used_mask))
				return idx;
			/* Release the Odd counter */
			clear_bit(idx, cpuc->used_mask);
		}
	}
	return -EAGAIN;
}