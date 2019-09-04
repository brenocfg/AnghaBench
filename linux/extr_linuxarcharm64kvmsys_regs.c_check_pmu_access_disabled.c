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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMUSERENR_EL0 ; 
 int __vcpu_sys_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 
 scalar_t__ vcpu_mode_priv (struct kvm_vcpu*) ; 

__attribute__((used)) static bool check_pmu_access_disabled(struct kvm_vcpu *vcpu, u64 flags)
{
	u64 reg = __vcpu_sys_reg(vcpu, PMUSERENR_EL0);
	bool enabled = (reg & flags) || vcpu_mode_priv(vcpu);

	if (!enabled)
		kvm_inject_undefined(vcpu);

	return !enabled;
}