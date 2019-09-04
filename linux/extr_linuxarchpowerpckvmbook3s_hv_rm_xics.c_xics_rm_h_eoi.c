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
typedef  scalar_t__ u32 ;
struct kvmppc_xics {int /*<<< orphan*/  real_mode; } ;
struct kvmppc_icp {int dummy; } ;
struct TYPE_6__ {struct kvmppc_icp* icp; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_2__* kvm; } ;
struct TYPE_4__ {struct kvmppc_xics* xics; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int H_TOO_HARD ; 
 scalar_t__ XICS_IPI ; 
 int check_too_hard (struct kvmppc_xics*,struct kvmppc_icp*) ; 
 int /*<<< orphan*/  icp_rm_down_cppr (struct kvmppc_xics*,struct kvmppc_icp*,unsigned long) ; 
 int ics_rm_eoi (struct kvm_vcpu*,scalar_t__) ; 

int xics_rm_h_eoi(struct kvm_vcpu *vcpu, unsigned long xirr)
{
	struct kvmppc_xics *xics = vcpu->kvm->arch.xics;
	struct kvmppc_icp *icp = vcpu->arch.icp;
	u32 irq = xirr & 0x00ffffff;

	if (!xics || !xics->real_mode)
		return H_TOO_HARD;

	/*
	 * ICP State: EOI
	 *
	 * Note: If EOI is incorrectly used by SW to lower the CPPR
	 * value (ie more favored), we do not check for rejection of
	 * a pending interrupt, this is a SW error and PAPR specifies
	 * that we don't have to deal with it.
	 *
	 * The sending of an EOI to the ICS is handled after the
	 * CPPR update
	 *
	 * ICP State: Down_CPPR which we handle
	 * in a separate function as it's shared with H_CPPR.
	 */
	icp_rm_down_cppr(xics, icp, xirr >> 24);

	/* IPIs have no EOI */
	if (irq == XICS_IPI)
		return check_too_hard(xics, icp);

	return ics_rm_eoi(vcpu, irq);
}