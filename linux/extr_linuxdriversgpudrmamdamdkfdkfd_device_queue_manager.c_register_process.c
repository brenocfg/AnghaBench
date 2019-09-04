#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct qcm_process_device {int /*<<< orphan*/  page_table_base; } ;
struct kfd_process_device {int /*<<< orphan*/  vm; } ;
struct TYPE_4__ {int (* update_qpd ) (struct device_queue_manager*,struct qcm_process_device*) ;} ;
struct device_queue_manager {TYPE_3__* dev; int /*<<< orphan*/  processes_count; TYPE_1__ asic_ops; int /*<<< orphan*/  queues; } ;
struct device_process_node {int /*<<< orphan*/  list; struct qcm_process_device* qpd; } ;
struct TYPE_6__ {int /*<<< orphan*/  kgd; TYPE_2__* kfd2kgd; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_compute_idle ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* get_process_page_dir ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dqm_lock (struct device_queue_manager*) ; 
 int /*<<< orphan*/  dqm_unlock (struct device_queue_manager*) ; 
 struct device_process_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kfd_process_device* qpd_to_pdd (struct qcm_process_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (struct device_queue_manager*,struct qcm_process_device*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int register_process(struct device_queue_manager *dqm,
					struct qcm_process_device *qpd)
{
	struct device_process_node *n;
	struct kfd_process_device *pdd;
	uint32_t pd_base;
	int retval;

	n = kzalloc(sizeof(*n), GFP_KERNEL);
	if (!n)
		return -ENOMEM;

	n->qpd = qpd;

	pdd = qpd_to_pdd(qpd);
	/* Retrieve PD base */
	pd_base = dqm->dev->kfd2kgd->get_process_page_dir(pdd->vm);

	dqm_lock(dqm);
	list_add(&n->list, &dqm->queues);

	/* Update PD Base in QPD */
	qpd->page_table_base = pd_base;

	retval = dqm->asic_ops.update_qpd(dqm, qpd);

	if (dqm->processes_count++ == 0)
		dqm->dev->kfd2kgd->set_compute_idle(dqm->dev->kgd, false);

	dqm_unlock(dqm);

	return retval;
}