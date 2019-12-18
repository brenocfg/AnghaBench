#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int vmid; } ;
struct queue {TYPE_3__ properties; TYPE_2__* process; } ;
struct qcm_process_device {int vmid; int /*<<< orphan*/  sh_hidden_private_base; int /*<<< orphan*/  page_table_base; } ;
struct device_queue_manager {int vmid_bitmap; TYPE_5__* dev; } ;
struct TYPE_6__ {int first_vmid_kfd; } ;
struct TYPE_10__ {int /*<<< orphan*/  kgd; TYPE_4__* kfd2kgd; TYPE_1__ vm_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_scratch_backing_va ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_vm_context_page_table_base ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  pasid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ffs (int) ; 
 int /*<<< orphan*/  kfd_flush_tlb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  program_sh_mem_settings (struct device_queue_manager*,struct qcm_process_device*) ; 
 int /*<<< orphan*/  qpd_to_pdd (struct qcm_process_device*) ; 
 int /*<<< orphan*/  set_pasid_vmid_mapping (struct device_queue_manager*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int allocate_vmid(struct device_queue_manager *dqm,
			struct qcm_process_device *qpd,
			struct queue *q)
{
	int bit, allocated_vmid;

	if (dqm->vmid_bitmap == 0)
		return -ENOMEM;

	bit = ffs(dqm->vmid_bitmap) - 1;
	dqm->vmid_bitmap &= ~(1 << bit);

	allocated_vmid = bit + dqm->dev->vm_info.first_vmid_kfd;
	pr_debug("vmid allocation %d\n", allocated_vmid);
	qpd->vmid = allocated_vmid;
	q->properties.vmid = allocated_vmid;

	set_pasid_vmid_mapping(dqm, q->process->pasid, q->properties.vmid);
	program_sh_mem_settings(dqm, qpd);

	/* qpd->page_table_base is set earlier when register_process()
	 * is called, i.e. when the first queue is created.
	 */
	dqm->dev->kfd2kgd->set_vm_context_page_table_base(dqm->dev->kgd,
			qpd->vmid,
			qpd->page_table_base);
	/* invalidate the VM context after pasid and vmid mapping is set up */
	kfd_flush_tlb(qpd_to_pdd(qpd));

	dqm->dev->kfd2kgd->set_scratch_backing_va(
		dqm->dev->kgd, qpd->sh_hidden_private_base, qpd->vmid);

	return 0;
}