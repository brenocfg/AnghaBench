#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; scalar_t__ is_active; } ;
struct queue {int /*<<< orphan*/  mqd_mem_obj; int /*<<< orphan*/  mqd; TYPE_2__ properties; int /*<<< orphan*/  list; int /*<<< orphan*/  sdma_id; } ;
struct qcm_process_device {int reset_wavefronts; int /*<<< orphan*/  queue_count; scalar_t__ is_debug; } ;
struct mqd_manager {int /*<<< orphan*/  (* uninit_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct mqd_manager* (* get_mqd_manager ) (struct device_queue_manager*,int /*<<< orphan*/ ) ;} ;
struct device_queue_manager {int /*<<< orphan*/  total_queue_count; int /*<<< orphan*/  queue_count; int /*<<< orphan*/  sdma_queue_count; TYPE_1__ ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ETIME ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 int /*<<< orphan*/  KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES ; 
 int /*<<< orphan*/  deallocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_sdma_queue (struct device_queue_manager*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 int execute_queues_cpsch (struct device_queue_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mqd_type_from_queue_type (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct mqd_manager* stub1 (struct device_queue_manager*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int destroy_queue_cpsch(struct device_queue_manager *dqm,
				struct qcm_process_device *qpd,
				struct queue *q)
{
	int retval;
	struct mqd_manager *mqd_mgr;
	bool preempt_all_queues;

	preempt_all_queues = false;

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

	mqd_mgr = dqm->ops.get_mqd_manager(dqm,
			get_mqd_type_from_queue_type(q->properties.type));
	if (!mqd_mgr) {
		retval = -ENOMEM;
		goto failed;
	}

	deallocate_doorbell(qpd, q);

	if (q->properties.type == KFD_QUEUE_TYPE_SDMA) {
		dqm->sdma_queue_count--;
		deallocate_sdma_queue(dqm, q->sdma_id);
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

	mqd_mgr->uninit_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);

	/*
	 * Unconditionally decrement this counter, regardless of the queue's
	 * type
	 */
	dqm->total_queue_count--;
	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);

	dqm_unlock(dqm);

	return retval;

failed:
failed_try_destroy_debugged_queue:

	dqm_unlock(dqm);
	return retval;
}