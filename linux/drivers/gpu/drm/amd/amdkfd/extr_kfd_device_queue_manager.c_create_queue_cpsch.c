#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; int is_evicted; scalar_t__ is_active; int /*<<< orphan*/  tma_addr; int /*<<< orphan*/  tba_addr; } ;
struct queue {TYPE_2__ properties; int /*<<< orphan*/  list; int /*<<< orphan*/  gart_mqd_addr; int /*<<< orphan*/  mqd_mem_obj; int /*<<< orphan*/  mqd; } ;
struct qcm_process_device {int /*<<< orphan*/  queue_count; int /*<<< orphan*/  queues_list; int /*<<< orphan*/  evicted; int /*<<< orphan*/  tma_addr; int /*<<< orphan*/  tba_addr; } ;
struct mqd_manager {int /*<<< orphan*/  (* init_mqd ) (struct mqd_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  (* allocate_mqd ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* init_sdma_vm ) (struct device_queue_manager*,struct queue*,struct qcm_process_device*) ;} ;
struct device_queue_manager {scalar_t__ total_queue_count; int /*<<< orphan*/  xgmi_sdma_queue_count; int /*<<< orphan*/  sdma_queue_count; int /*<<< orphan*/  queue_count; TYPE_1__ asic_ops; struct mqd_manager** mqd_mgrs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA_XGMI ; 
 int /*<<< orphan*/  KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES ; 
 int allocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int allocate_sdma_queue (struct device_queue_manager*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_sdma_queue (struct device_queue_manager*,struct queue*) ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 int execute_queues_cpsch (struct device_queue_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t get_mqd_type_from_queue_type (scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ max_num_of_queues_per_device ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct device_queue_manager*,struct queue*,struct qcm_process_device*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (struct mqd_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int create_queue_cpsch(struct device_queue_manager *dqm, struct queue *q,
			struct qcm_process_device *qpd)
{
	int retval;
	struct mqd_manager *mqd_mgr;

	if (dqm->total_queue_count >= max_num_of_queues_per_device) {
		pr_warn("Can't create new usermode queue because %d queues were already created\n",
				dqm->total_queue_count);
		retval = -EPERM;
		goto out;
	}

	if (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		dqm_lock(dqm);
		retval = allocate_sdma_queue(dqm, q);
		dqm_unlock(dqm);
		if (retval)
			goto out;
	}

	retval = allocate_doorbell(qpd, q);
	if (retval)
		goto out_deallocate_sdma_queue;

	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];

	if (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		dqm->asic_ops.init_sdma_vm(dqm, q, qpd);
	q->properties.tba_addr = qpd->tba_addr;
	q->properties.tma_addr = qpd->tma_addr;
	q->mqd_mem_obj = mqd_mgr->allocate_mqd(mqd_mgr->dev, &q->properties);
	if (!q->mqd_mem_obj) {
		retval = -ENOMEM;
		goto out_deallocate_doorbell;
	}

	dqm_lock(dqm);
	/*
	 * Eviction state logic: mark all queues as evicted, even ones
	 * not currently active. Restoring inactive queues later only
	 * updates the is_evicted flag but is a no-op otherwise.
	 */
	q->properties.is_evicted = !!qpd->evicted;
	mqd_mgr->init_mqd(mqd_mgr, &q->mqd, q->mqd_mem_obj,
				&q->gart_mqd_addr, &q->properties);

	list_add(&q->list, &qpd->queues_list);
	qpd->queue_count++;
	if (q->properties.is_active) {
		dqm->queue_count++;
		retval = execute_queues_cpsch(dqm,
				KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
	}

	if (q->properties.type == KFD_QUEUE_TYPE_SDMA)
		dqm->sdma_queue_count++;
	else if (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		dqm->xgmi_sdma_queue_count++;
	/*
	 * Unconditionally increment this counter, regardless of the queue's
	 * type or whether the queue is active.
	 */
	dqm->total_queue_count++;

	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);

	dqm_unlock(dqm);
	return retval;

out_deallocate_doorbell:
	deallocate_doorbell(qpd, q);
out_deallocate_sdma_queue:
	if (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		dqm_lock(dqm);
		deallocate_sdma_queue(dqm, q);
		dqm_unlock(dqm);
	}
out:
	return retval;
}