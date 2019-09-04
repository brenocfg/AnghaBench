#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  is_active; } ;
struct queue {int /*<<< orphan*/  mqd_mem_obj; int /*<<< orphan*/  mqd; TYPE_5__ properties; int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; TYPE_4__* process; int /*<<< orphan*/  gart_mqd_addr; } ;
struct qcm_process_device {int /*<<< orphan*/  vmid; int /*<<< orphan*/  sh_hidden_private_base; } ;
struct mqd_manager {int (* init_mqd ) (struct mqd_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ;int (* load_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,scalar_t__) ;int /*<<< orphan*/  (* uninit_mqd ) (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {struct mqd_manager* (* get_mqd_manager ) (struct device_queue_manager*,int /*<<< orphan*/ ) ;} ;
struct device_queue_manager {TYPE_3__* dev; TYPE_1__ ops; } ;
struct TYPE_13__ {scalar_t__ mm; } ;
struct TYPE_11__ {scalar_t__ mm; } ;
struct TYPE_10__ {int /*<<< orphan*/  kgd; TYPE_2__* kfd2kgd; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_scratch_backing_va ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KFD_MQD_TYPE_COMPUTE ; 
 scalar_t__ WARN (int,char*) ; 
 int allocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int allocate_hqd (struct device_queue_manager*,struct queue*) ; 
 TYPE_7__* current ; 
 int /*<<< orphan*/  deallocate_doorbell (struct qcm_process_device*,struct queue*) ; 
 int /*<<< orphan*/  deallocate_hqd (struct device_queue_manager*,struct queue*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mqd_manager* stub1 (struct device_queue_manager*,int /*<<< orphan*/ ) ; 
 int stub2 (struct mqd_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct mqd_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_compute_queue_nocpsch(struct device_queue_manager *dqm,
					struct queue *q,
					struct qcm_process_device *qpd)
{
	struct mqd_manager *mqd_mgr;
	int retval;

	mqd_mgr = dqm->ops.get_mqd_manager(dqm, KFD_MQD_TYPE_COMPUTE);
	if (!mqd_mgr)
		return -ENOMEM;

	retval = allocate_hqd(dqm, q);
	if (retval)
		return retval;

	retval = allocate_doorbell(qpd, q);
	if (retval)
		goto out_deallocate_hqd;

	retval = mqd_mgr->init_mqd(mqd_mgr, &q->mqd, &q->mqd_mem_obj,
				&q->gart_mqd_addr, &q->properties);
	if (retval)
		goto out_deallocate_doorbell;

	pr_debug("Loading mqd to hqd on pipe %d, queue %d\n",
			q->pipe, q->queue);

	dqm->dev->kfd2kgd->set_scratch_backing_va(
			dqm->dev->kgd, qpd->sh_hidden_private_base, qpd->vmid);

	if (!q->properties.is_active)
		return 0;

	if (WARN(q->process->mm != current->mm,
		 "should only run in user thread"))
		retval = -EFAULT;
	else
		retval = mqd_mgr->load_mqd(mqd_mgr, q->mqd, q->pipe, q->queue,
					   &q->properties, current->mm);
	if (retval)
		goto out_uninit_mqd;

	return 0;

out_uninit_mqd:
	mqd_mgr->uninit_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);
out_deallocate_doorbell:
	deallocate_doorbell(qpd, q);
out_deallocate_hqd:
	deallocate_hqd(dqm, q);

	return retval;
}