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
typedef  int /*<<< orphan*/  uint64_t ;
struct qcm_process_device {int /*<<< orphan*/  page_table_base; } ;
struct kfd_process_device {int /*<<< orphan*/  vm; } ;
struct TYPE_2__ {int (* update_qpd ) (struct device_queue_manager*,struct qcm_process_device*) ;} ;
struct device_queue_manager {int /*<<< orphan*/  dev; int /*<<< orphan*/  processes_count; TYPE_1__ asic_ops; int /*<<< orphan*/  queues; } ;
struct device_process_node {int /*<<< orphan*/  list; struct qcm_process_device* qpd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_amdkfd_gpuvm_get_process_page_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  kfd_inc_compute_active (int /*<<< orphan*/ ) ; 
 struct device_process_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct kfd_process_device* qpd_to_pdd (struct qcm_process_device*) ; 
 int stub1 (struct device_queue_manager*,struct qcm_process_device*) ; 

__attribute__((used)) static int register_process(struct device_queue_manager *dqm,
					struct qcm_process_device *qpd)
{
	struct device_process_node *n;
	struct kfd_process_device *pdd;
	uint64_t pd_base;
	int retval;

	n = kzalloc(sizeof(*n), GFP_KERNEL);
	if (!n)
		return -ENOMEM;

	n->qpd = qpd;

	pdd = qpd_to_pdd(qpd);
	/* Retrieve PD base */
	pd_base = amdgpu_amdkfd_gpuvm_get_process_page_dir(pdd->vm);

	dqm_lock(dqm);
	list_add(&n->list, &dqm->queues);

	/* Update PD Base in QPD */
	qpd->page_table_base = pd_base;
	pr_debug("Updated PD address to 0x%llx\n", pd_base);

	retval = dqm->asic_ops.update_qpd(dqm, qpd);

	dqm->processes_count++;

	dqm_unlock(dqm);

	/* Outside the DQM lock because under the DQM lock we can't do
	 * reclaim or take other locks that others hold while reclaiming.
	 */
	kfd_inc_compute_active(dqm->dev);

	return retval;
}