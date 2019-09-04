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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_events ; 
 int /*<<< orphan*/  pmc_reserve_mutex ; 
 int /*<<< orphan*/  release_pmc_hardware () ; 

__attribute__((used)) static void hw_perf_event_destroy(struct perf_event *event)
{
	/* Release PMC if this is the last perf event */
	if (!atomic_add_unless(&num_events, -1, 1)) {
		mutex_lock(&pmc_reserve_mutex);
		if (atomic_dec_return(&num_events) == 0)
			release_pmc_hardware();
		mutex_unlock(&pmc_reserve_mutex);
	}
}