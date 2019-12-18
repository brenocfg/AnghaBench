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
struct queue {TYPE_2__ properties; int /*<<< orphan*/  list; int /*<<< orphan*/  mqd_mem_obj; int /*<<< orphan*/  mqd; int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; } ;
struct qcm_process_device {int reset_wavefronts; int /*<<< orphan*/  queue_count; TYPE_1__* pqm; int /*<<< orphan*/  queues_list; } ;
struct mqd_manager {int (* destroy_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* free_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct device_queue_manager {int /*<<< orphan*/  queue_count; int /*<<< orphan*/  dev; int /*<<< orphan*/  total_queue_count; int /*<<< orphan*/  xgmi_sdma_queue_count; int /*<<< orphan*/  sdma_queue_count; struct mqd_manager** mqd_mgrs; } ;
struct TYPE_3__ {int /*<<< orphan*/  process; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIME ; 
 int /*<<< orphan*/  KFD_PREEMPT_TYPE_WAVEFRONT_RESET ; 
 scalar_t__ KFD_QUEUE_TYPE_COMPUTE ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA_XGMI ; 
 int /*<<< orphan*/  KFD_UNMAP_LATENCY_MS ; 
 int /*<<< orphan*/  dbgdev_wave_reset_wavefronts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deallocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_hqd (struct device_queue_manager*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_sdma_queue (struct device_queue_manager*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_vmid (struct device_queue_manager*,struct qcm_process_device*,struct queue*) ; 
 size_t get_mqd_type_from_queue_type (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int destroy_queue_nocpsch_locked(struct device_queue_manager *dqm,
				struct qcm_process_device *qpd,
				struct queue *q)
{
	int retval;
	struct mqd_manager *mqd_mgr;

	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];

	if (q->properties.type == KFD_QUEUE_TYPE_COMPUTE) {
		deallocate_hqd(dqm, q);
	} else if (q->properties.type == KFD_QUEUE_TYPE_SDMA) {
		dqm->sdma_queue_count--;
		deallocate_sdma_queue(dqm, q);
	} else if (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		dqm->xgmi_sdma_queue_count--;
		deallocate_sdma_queue(dqm, q);
	} else {
		pr_debug("q->properties.type %d is invalid\n",
				q->properties.type);
		return -EINVAL;
	}
	dqm->total_queue_count--;

	deallocate_doorbell(qpd, q);

	retval = mqd_mgr->destroy_mqd(mqd_mgr, q->mqd,
				KFD_PREEMPT_TYPE_WAVEFRONT_RESET,
				KFD_UNMAP_LATENCY_MS,
				q->pipe, q->queue);
	if (retval == -ETIME)
		qpd->reset_wavefronts = true;

	mqd_mgr->free_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);

	list_del(&q->list);
	if (list_empty(&qpd->queues_list)) {
		if (qpd->reset_wavefronts) {
			pr_warn("Resetting wave fronts (nocpsch) on dev %p\n",
					dqm->dev);
			/* dbgdev_wave_reset_wavefronts has to be called before
			 * deallocate_vmid(), i.e. when vmid is still in use.
			 */
			dbgdev_wave_reset_wavefronts(dqm->dev,
					qpd->pqm->process);
			qpd->reset_wavefronts = false;
		}

		deallocate_vmid(dqm, qpd, q);
	}
	qpd->queue_count--;
	if (q->properties.is_active)
		dqm->queue_count--;

	return retval;
}