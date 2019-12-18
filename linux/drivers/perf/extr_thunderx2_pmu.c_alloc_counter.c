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
struct tx2_uncore_pmu {int max_counters; int /*<<< orphan*/  active_counters; } ;

/* Variables and functions */
 int ENOSPC ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_counter(struct tx2_uncore_pmu *tx2_pmu)
{
	int counter;

	counter = find_first_zero_bit(tx2_pmu->active_counters,
				tx2_pmu->max_counters);
	if (counter == tx2_pmu->max_counters)
		return -ENOSPC;

	set_bit(counter, tx2_pmu->active_counters);
	return counter;
}