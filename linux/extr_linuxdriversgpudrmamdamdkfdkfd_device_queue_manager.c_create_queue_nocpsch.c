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
struct TYPE_2__ {int is_evicted; scalar_t__ queue_size; scalar_t__ queue_percent; scalar_t__ queue_address; scalar_t__ type; scalar_t__ is_active; int /*<<< orphan*/  tma_addr; int /*<<< orphan*/  tba_addr; int /*<<< orphan*/  vmid; } ;
struct queue {TYPE_1__ properties; int /*<<< orphan*/  list; } ;
struct qcm_process_device {int /*<<< orphan*/  queue_count; int /*<<< orphan*/  queues_list; int /*<<< orphan*/  tma_addr; int /*<<< orphan*/  tba_addr; scalar_t__ evicted; int /*<<< orphan*/  vmid; } ;
struct device_queue_manager {scalar_t__ total_queue_count; int /*<<< orphan*/  sdma_queue_count; int /*<<< orphan*/  queue_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ KFD_QUEUE_TYPE_COMPUTE ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 int allocate_vmid (struct device_queue_manager*,struct qcm_process_device*,struct queue*) ; 
 int create_compute_queue_nocpsch (struct device_queue_manager*,struct queue*,struct qcm_process_device*) ; 
 int create_sdma_queue_nocpsch (struct device_queue_manager*,struct queue*,struct qcm_process_device*) ; 
 int /*<<< orphan*/  deallocate_vmid (struct device_queue_manager*,struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ max_num_of_queues_per_device ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  print_queue (struct queue*) ; 

__attribute__((used)) static int create_queue_nocpsch(struct device_queue_manager *dqm,
				struct queue *q,
				struct qcm_process_device *qpd)
{
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
	 * Eviction state logic: we only mark active queues as evicted
	 * to avoid the overhead of restoring inactive queues later
	 */
	if (qpd->evicted)
		q->properties.is_evicted = (q->properties.queue_size > 0 &&
					    q->properties.queue_percent > 0 &&
					    q->properties.queue_address != 0);

	q->properties.tba_addr = qpd->tba_addr;
	q->properties.tma_addr = qpd->tma_addr;

	if (q->properties.type == KFD_QUEUE_TYPE_COMPUTE)
		retval = create_compute_queue_nocpsch(dqm, q, qpd);
	else if (q->properties.type == KFD_QUEUE_TYPE_SDMA)
		retval = create_sdma_queue_nocpsch(dqm, q, qpd);
	else
		retval = -EINVAL;

	if (retval) {
		if (list_empty(&qpd->queues_list))
			deallocate_vmid(dqm, qpd, q);
		goto out_unlock;
	}

	list_add(&q->list, &qpd->queues_list);
	qpd->queue_count++;
	if (q->properties.is_active)
		dqm->queue_count++;

	if (q->properties.type == KFD_QUEUE_TYPE_SDMA)
		dqm->sdma_queue_count++;

	/*
	 * Unconditionally increment this counter, regardless of the queue's
	 * type or whether the queue is active.
	 */
	dqm->total_queue_count++;
	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);

out_unlock:
	dqm_unlock(dqm);
	return retval;
}