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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_queue_manager {int is_hws_hang; int /*<<< orphan*/  hw_exception_work; } ;
typedef  enum kfd_unmap_queues_filter { ____Placeholder_kfd_unmap_queues_filter } kfd_unmap_queues_filter ;

/* Variables and functions */
 int EIO ; 
 int map_queues_cpsch (struct device_queue_manager*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int unmap_queues_cpsch (struct device_queue_manager*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_queues_cpsch(struct device_queue_manager *dqm,
				enum kfd_unmap_queues_filter filter,
				uint32_t filter_param)
{
	int retval;

	if (dqm->is_hws_hang)
		return -EIO;
	retval = unmap_queues_cpsch(dqm, filter, filter_param);
	if (retval) {
		pr_err("The cp might be in an unrecoverable state due to an unsuccessful queues preemption\n");
		dqm->is_hws_hang = true;
		schedule_work(&dqm->hw_exception_work);
		return retval;
	}

	return map_queues_cpsch(dqm);
}