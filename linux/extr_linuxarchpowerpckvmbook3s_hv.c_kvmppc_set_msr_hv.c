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
typedef  int u64 ;
struct TYPE_3__ {int msr; } ;
struct TYPE_4__ {TYPE_1__ shregs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int MSR_TS_MASK ; 
 int /*<<< orphan*/  kvmppc_end_cede (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvmppc_set_msr_hv(struct kvm_vcpu *vcpu, u64 msr)
{
	/*
	 * Check for illegal transactional state bit combination
	 * and if we find it, force the TS field to a safe state.
	 */
	if ((msr & MSR_TS_MASK) == MSR_TS_MASK)
		msr &= ~MSR_TS_MASK;
	vcpu->arch.shregs.msr = msr;
	kvmppc_end_cede(vcpu);
}