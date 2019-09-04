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
struct TYPE_2__ {unsigned int hflags; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned int HF_SMM_MASK ; 
 int /*<<< orphan*/  kvm_smm_changed (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_set_hflags(struct kvm_vcpu *vcpu, unsigned emul_flags)
{
	unsigned changed = vcpu->arch.hflags ^ emul_flags;

	vcpu->arch.hflags = emul_flags;

	if (changed & HF_SMM_MASK)
		kvm_smm_changed(vcpu);
}