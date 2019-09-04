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
struct TYPE_2__ {int fpu_enabled; int msa_enabled; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;
struct kvm_enable_cap {int cap; scalar_t__* args; scalar_t__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_CAP_MIPS_FPU 129 
#define  KVM_CAP_MIPS_MSA 128 
 int /*<<< orphan*/  kvm_vm_ioctl_check_extension (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kvm_vcpu_ioctl_enable_cap(struct kvm_vcpu *vcpu,
				     struct kvm_enable_cap *cap)
{
	int r = 0;

	if (!kvm_vm_ioctl_check_extension(vcpu->kvm, cap->cap))
		return -EINVAL;
	if (cap->flags)
		return -EINVAL;
	if (cap->args[0])
		return -EINVAL;

	switch (cap->cap) {
	case KVM_CAP_MIPS_FPU:
		vcpu->arch.fpu_enabled = true;
		break;
	case KVM_CAP_MIPS_MSA:
		vcpu->arch.msa_enabled = true;
		break;
	default:
		r = -EINVAL;
		break;
	}

	return r;
}