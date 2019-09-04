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
struct qcm_process_device {int is_debug; } ;
struct kernel_queue {int /*<<< orphan*/  list; } ;
struct device_queue_manager {int /*<<< orphan*/  total_queue_count; int /*<<< orphan*/  queue_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  execute_queues_cpsch (struct device_queue_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_kernel_queue_cpsch(struct device_queue_manager *dqm,
					struct kernel_queue *kq,
					struct qcm_process_device *qpd)
{
	dqm_lock(dqm);
	list_del(&kq->list);
	dqm->queue_count--;
	qpd->is_debug = false;
	execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES, 0);
	/*
	 * Unconditionally decrement this counter, regardless of the queue's
	 * type.
	 */
	dqm->total_queue_count--;
	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);
	dqm_unlock(dqm);
}