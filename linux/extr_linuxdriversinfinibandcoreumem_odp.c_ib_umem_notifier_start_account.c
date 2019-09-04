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
struct ib_umem {TYPE_1__* odp_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  umem_mutex; int /*<<< orphan*/  notifier_completion; int /*<<< orphan*/  notifiers_count; scalar_t__ mn_counters_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_umem_notifier_start_account(struct ib_umem *item)
{
	mutex_lock(&item->odp_data->umem_mutex);

	/* Only update private counters for this umem if it has them.
	 * Otherwise skip it. All page faults will be delayed for this umem. */
	if (item->odp_data->mn_counters_active) {
		int notifiers_count = item->odp_data->notifiers_count++;

		if (notifiers_count == 0)
			/* Initialize the completion object for waiting on
			 * notifiers. Since notifier_count is zero, no one
			 * should be waiting right now. */
			reinit_completion(&item->odp_data->notifier_completion);
	}
	mutex_unlock(&item->odp_data->umem_mutex);
}