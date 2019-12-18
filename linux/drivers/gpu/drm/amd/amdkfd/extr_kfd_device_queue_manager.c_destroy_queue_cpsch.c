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
struct TYPE_2__ {scalar_t__ type; scalar_t__ is_active; } ;
struct queue {int /*<<< orphan*/  mqd_mem_obj; int /*<<< orphan*/  mqd; TYPE_1__ properties; int /*<<< orphan*/  list; } ;
struct qcm_process_device {int reset_wavefronts; int /*<<< orphan*/  queue_count; scalar_t__ is_debug; } ;
struct mqd_manager {int /*<<< orphan*/  (* free_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct device_queue_manager {int /*<<< orphan*/  total_queue_count; int /*<<< orphan*/  queue_count; int /*<<< orphan*/  xgmi_sdma_queue_count; int /*<<< orphan*/  sdma_queue_count; struct mqd_manager** mqd_mgrs; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIME ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA_XGMI ; 
 int /*<<< orphan*/  KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES ; 
 int /*<<< orphan*/  deallocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_sdma_queue (struct device_queue_manager*,struct queue*) ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 int execute_queues_cpsch (struct device_queue_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t get_mqd_type_from_queue_type (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int destroy_queue_cpsch(struct device_queue_manager *dqm,
				struct qcm_process_device *qpd,
				struct queue *q)
{
	int retval;
	struct mqd_manager *mqd_mgr;

	retval = 0;

	/* remove queue from list to prevent rescheduling after preemption */
	dqm_lock(dqm);

	if (qpd->is_debug) {
		/*
		 * error, currently we do not allow to destroy a queue
		 * of a currently debugged process
		 */
		retval = -EBUSY;
		goto failed_try_destroy_debugged_queue;

	}

	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];

	deallocate_doorbell(qpd, q);

	if (q->properties.type == KFD_QUEUE_TYPE_SDMA) {
		dqm->sdma_queue_count--;
		deallocate_sdma_queue(dqm, q);
	} else if (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		dqm->xgmi_sdma_queue_count--;
		deallocate_sdma_queue(dqm, q);
	}

	list_del(&q->list);
	qpd->queue_count--;
	if (q->properties.is_active) {
		dqm->queue_count--;
		retval = execute_queues_cpsch(dqm,
				KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
		if (retval == -ETIME)
			qpd->reset_wavefronts = true;
	}

	/*
	 * Unconditionally decrement this counter, regardless of the queue's
	 * type
	 */
	dqm->total_queue_count--;
	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);

	dqm_unlock(dqm);

	/* Do free_mqd after dqm_unlock(dqm) to avoid circular locking */
	mqd_mgr->free_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);

	return retval;

failed_try_destroy_debugged_queue:

	dqm_unlock(dqm);
	return retval;
}