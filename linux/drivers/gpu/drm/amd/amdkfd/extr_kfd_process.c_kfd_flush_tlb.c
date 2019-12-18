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
struct TYPE_6__ {int /*<<< orphan*/  vmid; } ;
struct kfd_process_device {TYPE_1__* process; TYPE_3__ qpd; struct kfd_dev* dev; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_2__* dqm; struct kfd2kgd_calls* kfd2kgd; } ;
struct kfd2kgd_calls {int /*<<< orphan*/  (* invalidate_tlbs ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* invalidate_tlbs_vmid ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ sched_policy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pasid; } ;

/* Variables and functions */
 scalar_t__ KFD_SCHED_POLICY_NO_HWS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kfd_flush_tlb(struct kfd_process_device *pdd)
{
	struct kfd_dev *dev = pdd->dev;
	const struct kfd2kgd_calls *f2g = dev->kfd2kgd;

	if (dev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS) {
		/* Nothing to flush until a VMID is assigned, which
		 * only happens when the first queue is created.
		 */
		if (pdd->qpd.vmid)
			f2g->invalidate_tlbs_vmid(dev->kgd, pdd->qpd.vmid);
	} else {
		f2g->invalidate_tlbs(dev->kgd, pdd->process->pasid);
	}
}