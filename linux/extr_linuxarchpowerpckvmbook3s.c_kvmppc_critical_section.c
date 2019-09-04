#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ulong ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int MSR_PR ; 
 int MSR_SF ; 
 scalar_t__ is_kvmppc_hv_enabled (int /*<<< orphan*/ ) ; 
 int kvmppc_get_critical (struct kvm_vcpu*) ; 
 int kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool kvmppc_critical_section(struct kvm_vcpu *vcpu)
{
	ulong crit_raw;
	ulong crit_r1;
	bool crit;

	if (is_kvmppc_hv_enabled(vcpu->kvm))
		return false;

	crit_raw = kvmppc_get_critical(vcpu);
	crit_r1 = kvmppc_get_gpr(vcpu, 1);

	/* Truncate crit indicators in 32 bit mode */
	if (!(kvmppc_get_msr(vcpu) & MSR_SF)) {
		crit_raw &= 0xffffffff;
		crit_r1 &= 0xffffffff;
	}

	/* Critical section when crit == r1 */
	crit = (crit_raw == crit_r1);
	/* ... and we're in supervisor mode */
	crit = crit && !(kvmppc_get_msr(vcpu) & MSR_PR);

	return crit;
}