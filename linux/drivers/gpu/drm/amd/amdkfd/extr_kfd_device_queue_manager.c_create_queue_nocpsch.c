#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int is_evicted; scalar_t__ type; scalar_t__ is_active; int /*<<< orphan*/  tma_addr; int /*<<< orphan*/  tba_addr; int /*<<< orphan*/  vmid; } ;
struct queue {TYPE_3__ properties; int /*<<< orphan*/  mqd_mem_obj; int /*<<< orphan*/  mqd; int /*<<< orphan*/  list; int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; TYPE_2__* process; int /*<<< orphan*/  gart_mqd_addr; } ;
struct qcm_process_device {int /*<<< orphan*/  queues_list; int /*<<< orphan*/  queue_count; int /*<<< orphan*/  tma_addr; int /*<<< orphan*/  tba_addr; int /*<<< orphan*/  evicted; int /*<<< orphan*/  vmid; } ;
struct mqd_manager {int (* load_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ;int /*<<< orphan*/  (* free_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init_mqd ) (struct mqd_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  (* allocate_mqd ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* init_sdma_vm ) (struct device_queue_manager*,struct queue*,struct qcm_process_device*) ;} ;
struct device_queue_manager {scalar_t__ total_queue_count; int /*<<< orphan*/  xgmi_sdma_queue_count; int /*<<< orphan*/  sdma_queue_count; int /*<<< orphan*/  queue_count; TYPE_1__ asic_ops; struct mqd_manager** mqd_mgrs; } ;
struct TYPE_10__ {scalar_t__ mm; } ;
struct TYPE_8__ {scalar_t__ mm; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ KFD_QUEUE_TYPE_COMPUTE ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA_XGMI ; 
 scalar_t__ WARN (int,char*) ; 
 int allocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int allocate_hqd (struct device_queue_manager*,struct queue*) ; 
 int allocate_sdma_queue (struct device_queue_manager*,struct queue*) ; 
 int allocate_vmid (struct device_queue_manager*,struct qcm_process_device*,struct queue*) ; 
 TYPE_6__* current ; 
 int /*<<< orphan*/  deallocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_hqd (struct device_queue_manager*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_sdma_queue (struct device_queue_manager*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_vmid (struct device_queue_manager*,struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 size_t get_mqd_type_from_queue_type (scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ max_num_of_queues_per_device ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  print_queue (struct queue*) ; 
 int /*<<< orphan*/  stub1 (struct device_queue_manager*,struct queue*,struct qcm_process_device*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (struct mqd_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int stub4 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_queue_nocpsch(struct device_queue_manager *dqm,
				struct queue *q,
				struct qcm_process_device *qpd)
{
	struct mqd_manager *mqd_mgr;
	int retval;

	print_queue(q);

	dqm_lock(dqm);

	if (dqm->total_queue_count >= max_num_of_queues_per_device) {
		pr_warn("Can't create new usermode queue because %d queues were already created\n",
				dqm->total_queue_count);
		retval = -EPERM;
		goto out_unlock;
	}

	if (list_empty(&qpd->queues_list)) {
		retval = allocate_vmid(dqm, qpd, q);
		if (retval)
			goto out_unlock;
	}
	q->properties.vmid = qpd->vmid;
	/*
	 * Eviction state logic: mark all queues as evicted, even ones
	 * not currently active. Restoring inactive queues later only
	 * updates the is_evicted flag but is a no-op otherwise.
	 */
	q->properties.is_evicted = !!qpd->evicted;

	q->properties.tba_addr = qpd->tba_addr;
	q->properties.tma_addr = qpd->tma_addr;

	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];
	if (q->properties.type == KFD_QUEUE_TYPE_COMPUTE) {
		retval = allocate_hqd(dqm, q);
		if (retval)
			goto deallocate_vmid;
		pr_debug("Loading mqd to hqd on pipe %d, queue %d\n",
			q->pipe, q->queue);
	} else if (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		retval = allocate_sdma_queue(dqm, q);
		if (retval)
			goto deallocate_vmid;
		dqm->asic_ops.init_sdma_vm(dqm, q, qpd);
	}

	retval = allocate_doorbell(qpd, q);
	if (retval)
		goto out_deallocate_hqd;

	/* Temporarily release dqm lock to avoid a circular lock dependency */
	dqm_unlock(dqm);
	q->mqd_mem_obj = mqd_mgr->allocate_mqd(mqd_mgr->dev, &q->properties);
	dqm_lock(dqm);

	if (!q->mqd_mem_obj) {
		retval = -ENOMEM;
		goto out_deallocate_doorbell;
	}
	mqd_mgr->init_mqd(mqd_mgr, &q->mqd, q->mqd_mem_obj,
				&q->gart_mqd_addr, &q->properties);
	if (q->properties.is_active) {

		if (WARN(q->process->mm != current->mm,
					"should only run in user thread"))
			retval = -EFAULT;
		else
			retval = mqd_mgr->load_mqd(mqd_mgr, q->mqd, q->pipe,
					q->queue, &q->properties, current->mm);
		if (retval)
			goto out_free_mqd;
	}

	list_add(&q->list, &qpd->queues_list);
	qpd->queue_count++;
	if (q->properties.is_active)
		dqm->queue_count++;

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
	goto out_unlock;

out_free_mqd:
	mqd_mgr->free_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);
out_deallocate_doorbell:
	deallocate_doorbell(qpd, q);
out_deallocate_hqd:
	if (q->properties.type == KFD_QUEUE_TYPE_COMPUTE)
		deallocate_hqd(dqm, q);
	else if (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		deallocate_sdma_queue(dqm, q);
deallocate_vmid:
	if (list_empty(&qpd->queues_list))
		deallocate_vmid(dqm, qpd, q);
out_unlock:
	dqm_unlock(dqm);
	return retval;
}