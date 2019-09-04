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
typedef  int u64 ;
struct kvmppc_xive_vcpu {scalar_t__ mfrr; scalar_t__ cppr; } ;
struct TYPE_2__ {struct kvmppc_xive_vcpu* xive_vcpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int KVM_REG_PPC_ICP_CPPR_SHIFT ; 
 int KVM_REG_PPC_ICP_MFRR_SHIFT ; 
 int KVM_REG_PPC_ICP_PPRI_SHIFT ; 

u64 kvmppc_xive_get_icp(struct kvm_vcpu *vcpu)
{
	struct kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;

	if (!xc)
		return 0;

	/* Return the per-cpu state for state saving/migration */
	return (u64)xc->cppr << KVM_REG_PPC_ICP_CPPR_SHIFT |
	       (u64)xc->mfrr << KVM_REG_PPC_ICP_MFRR_SHIFT |
	       (u64)0xff << KVM_REG_PPC_ICP_PPRI_SHIFT;
}