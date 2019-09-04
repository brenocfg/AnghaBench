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

/* Variables and functions */
 int /*<<< orphan*/ * itmt_sysctl_header ; 
 int /*<<< orphan*/  itmt_update_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebuild_sched_domains () ; 
 int sched_itmt_capable ; 
 scalar_t__ sysctl_sched_itmt_enabled ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ *) ; 
 int x86_topology_update ; 

void sched_clear_itmt_support(void)
{
	mutex_lock(&itmt_update_mutex);

	if (!sched_itmt_capable) {
		mutex_unlock(&itmt_update_mutex);
		return;
	}
	sched_itmt_capable = false;

	if (itmt_sysctl_header) {
		unregister_sysctl_table(itmt_sysctl_header);
		itmt_sysctl_header = NULL;
	}

	if (sysctl_sched_itmt_enabled) {
		/* disable sched_itmt if we are no longer ITMT capable */
		sysctl_sched_itmt_enabled = 0;
		x86_topology_update = true;
		rebuild_sched_domains();
	}

	mutex_unlock(&itmt_update_mutex);
}