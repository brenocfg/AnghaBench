#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; int is_active; } ;
struct queue {TYPE_1__ properties; int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; int /*<<< orphan*/  mqd; TYPE_3__* process; int /*<<< orphan*/  device; } ;
struct mqd_manager {int (* destroy_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* load_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ;int /*<<< orphan*/  (* update_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,TYPE_1__*) ;} ;
struct kfd_process_device {int dummy; } ;
struct device_queue_manager {scalar_t__ sched_policy; int /*<<< orphan*/  queue_count; struct mqd_manager** mqd_mgrs; } ;
struct TYPE_7__ {scalar_t__ mm; } ;
struct TYPE_6__ {scalar_t__ mm; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN ; 
 scalar_t__ KFD_QUEUE_TYPE_COMPUTE ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA_XGMI ; 
 scalar_t__ KFD_SCHED_POLICY_NO_HWS ; 
 int /*<<< orphan*/  KFD_UNMAP_LATENCY_MS ; 
 int /*<<< orphan*/  KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES ; 
 scalar_t__ WARN (int,char*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 size_t get_mqd_type_from_queue_type (scalar_t__) ; 
 struct kfd_process_device* kfd_get_process_device_data (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int map_queues_cpsch (struct device_queue_manager*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mqd_manager*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int stub3 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int unmap_queues_cpsch (struct device_queue_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_queue(struct device_queue_manager *dqm, struct queue *q)
{
	int retval = 0;
	struct mqd_manager *mqd_mgr;
	struct kfd_process_device *pdd;
	bool prev_active = false;

	dqm_lock(dqm);
	pdd = kfd_get_process_device_data(q->device, q->process);
	if (!pdd) {
		retval = -ENODEV;
		goto out_unlock;
	}
	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];

	/* Save previous activity state for counters */
	prev_active = q->properties.is_active;

	/* Make sure the queue is unmapped before updating the MQD */
	if (dqm->sched_policy != KFD_SCHED_POLICY_NO_HWS) {
		retval = unmap_queues_cpsch(dqm,
				KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
		if (retval) {
			pr_err("unmap queue failed\n");
			goto out_unlock;
		}
	} else if (prev_active &&
		   (q->properties.type == KFD_QUEUE_TYPE_COMPUTE ||
		    q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		    q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) {
		retval = mqd_mgr->destroy_mqd(mqd_mgr, q->mqd,
				KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN,
				KFD_UNMAP_LATENCY_MS, q->pipe, q->queue);
		if (retval) {
			pr_err("destroy mqd failed\n");
			goto out_unlock;
		}
	}

	mqd_mgr->update_mqd(mqd_mgr, q->mqd, &q->properties);

	/*
	 * check active state vs. the previous state and modify
	 * counter accordingly. map_queues_cpsch uses the
	 * dqm->queue_count to determine whether a new runlist must be
	 * uploaded.
	 */
	if (q->properties.is_active && !prev_active)
		dqm->queue_count++;
	else if (!q->properties.is_active && prev_active)
		dqm->queue_count--;

	if (dqm->sched_policy != KFD_SCHED_POLICY_NO_HWS)
		retval = map_queues_cpsch(dqm);
	else if (q->properties.is_active &&
		 (q->properties.type == KFD_QUEUE_TYPE_COMPUTE ||
		  q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		  q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) {
		if (WARN(q->process->mm != current->mm,
			 "should only run in user thread"))
			retval = -EFAULT;
		else
			retval = mqd_mgr->load_mqd(mqd_mgr, q->mqd,
						   q->pipe, q->queue,
						   &q->properties, current->mm);
	}

out_unlock:
	dqm_unlock(dqm);
	return retval;
}