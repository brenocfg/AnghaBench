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
struct device_queue_manager {scalar_t__ queue_count; scalar_t__ processes_count; int active_runlist; int /*<<< orphan*/  queues; int /*<<< orphan*/  packets; } ;

/* Variables and functions */
 int pm_send_runlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int map_queues_cpsch(struct device_queue_manager *dqm)
{
	int retval;

	if (dqm->queue_count <= 0 || dqm->processes_count <= 0)
		return 0;

	if (dqm->active_runlist)
		return 0;

	retval = pm_send_runlist(&dqm->packets, &dqm->queues);
	if (retval) {
		pr_err("failed to execute runlist\n");
		return retval;
	}
	dqm->active_runlist = true;

	return retval;
}