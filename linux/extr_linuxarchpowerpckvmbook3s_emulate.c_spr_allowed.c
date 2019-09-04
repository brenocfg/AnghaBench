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
struct TYPE_2__ {scalar_t__ papr_enabled; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum priv_level { ____Placeholder_priv_level } priv_level ;

/* Variables and functions */
 int MSR_PR ; 
 int PRIV_PROBLEM ; 
 int PRIV_SUPER ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 

__attribute__((used)) static bool spr_allowed(struct kvm_vcpu *vcpu, enum priv_level level)
{
	/* PAPR VMs only access supervisor SPRs */
	if (vcpu->arch.papr_enabled && (level > PRIV_SUPER))
		return false;

	/* Limit user space to its own small SPR set */
	if ((kvmppc_get_msr(vcpu) & MSR_PR) && level > PRIV_PROBLEM)
		return false;

	return true;
}