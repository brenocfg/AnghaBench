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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_enable_cap {int cap; int /*<<< orphan*/ * args; scalar_t__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_CAP_HYPERV_SYNIC 129 
#define  KVM_CAP_HYPERV_SYNIC2 128 
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int kvm_hv_activate_synic (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int kvm_vcpu_ioctl_enable_cap(struct kvm_vcpu *vcpu,
				     struct kvm_enable_cap *cap)
{
	if (cap->flags)
		return -EINVAL;

	switch (cap->cap) {
	case KVM_CAP_HYPERV_SYNIC2:
		if (cap->args[0])
			return -EINVAL;
	case KVM_CAP_HYPERV_SYNIC:
		if (!irqchip_in_kernel(vcpu->kvm))
			return -EINVAL;
		return kvm_hv_activate_synic(vcpu, cap->cap ==
					     KVM_CAP_HYPERV_SYNIC2);
	default:
		return -EINVAL;
	}
}