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
struct kvm_enable_cap {int cap; scalar_t__ flags; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int kvm_vm_ioctl_enable_cap(struct kvm *kvm,
				   struct kvm_enable_cap *cap)
{
	int r;

	if (cap->flags)
		return -EINVAL;

	switch (cap->cap) {
#ifdef CONFIG_KVM_BOOK3S_64_HANDLER
	case KVM_CAP_PPC_ENABLE_HCALL: {
		unsigned long hcall = cap->args[0];

		r = -EINVAL;
		if (hcall > MAX_HCALL_OPCODE || (hcall & 3) ||
		    cap->args[1] > 1)
			break;
		if (!kvmppc_book3s_hcall_implemented(kvm, hcall))
			break;
		if (cap->args[1])
			set_bit(hcall / 4, kvm->arch.enabled_hcalls);
		else
			clear_bit(hcall / 4, kvm->arch.enabled_hcalls);
		r = 0;
		break;
	}
	case KVM_CAP_PPC_SMT: {
		unsigned long mode = cap->args[0];
		unsigned long flags = cap->args[1];

		r = -EINVAL;
		if (kvm->arch.kvm_ops->set_smt_mode)
			r = kvm->arch.kvm_ops->set_smt_mode(kvm, mode, flags);
		break;
	}
#endif
	default:
		r = -EINVAL;
		break;
	}

	return r;
}