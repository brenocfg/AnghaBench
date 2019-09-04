#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct kvmppc_xics {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  raw; } ;
struct kvmppc_icp {int rm_action; int /*<<< orphan*/  rm_eoied_irq; int /*<<< orphan*/  n_rm_notify_eoi; int /*<<< orphan*/  rm_resend_icp; int /*<<< orphan*/  n_rm_check_resend; int /*<<< orphan*/  rm_kick_target; int /*<<< orphan*/  n_rm_kick_vcpu; int /*<<< orphan*/  rm_dbgtgt; TYPE_3__ rm_dbgstate; } ;
struct TYPE_6__ {struct kvmppc_icp* icp; } ;
struct kvm_vcpu {TYPE_4__* kvm; TYPE_2__ arch; } ;
struct TYPE_5__ {struct kvmppc_xics* xics; } ;
struct TYPE_8__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int H_SUCCESS ; 
 int /*<<< orphan*/  XICS_DBG (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XICS_RM_CHECK_RESEND ; 
 int XICS_RM_KICK_VCPU ; 
 int XICS_RM_NOTIFY_EOI ; 
 int /*<<< orphan*/  icp_check_resend (struct kvmppc_xics*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_notify_acked_irq (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_fast_vcpu_kick (int /*<<< orphan*/ ) ; 

int kvmppc_xics_rm_complete(struct kvm_vcpu *vcpu, u32 hcall)
{
	struct kvmppc_xics *xics = vcpu->kvm->arch.xics;
	struct kvmppc_icp *icp = vcpu->arch.icp;

	XICS_DBG("XICS_RM: H_%x completing, act: %x state: %lx tgt: %p\n",
		 hcall, icp->rm_action, icp->rm_dbgstate.raw, icp->rm_dbgtgt);

	if (icp->rm_action & XICS_RM_KICK_VCPU) {
		icp->n_rm_kick_vcpu++;
		kvmppc_fast_vcpu_kick(icp->rm_kick_target);
	}
	if (icp->rm_action & XICS_RM_CHECK_RESEND) {
		icp->n_rm_check_resend++;
		icp_check_resend(xics, icp->rm_resend_icp);
	}
	if (icp->rm_action & XICS_RM_NOTIFY_EOI) {
		icp->n_rm_notify_eoi++;
		kvm_notify_acked_irq(vcpu->kvm, 0, icp->rm_eoied_irq);
	}

	icp->rm_action = 0;

	return H_SUCCESS;
}