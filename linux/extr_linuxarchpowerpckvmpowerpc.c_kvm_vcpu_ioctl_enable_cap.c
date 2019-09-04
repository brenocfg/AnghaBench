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
struct TYPE_2__ {int osi_enabled; int papr_enabled; int /*<<< orphan*/  epr_flags; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_enable_cap {int cap; int /*<<< orphan*/ * args; scalar_t__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVMPPC_EPR_USER ; 
#define  KVM_CAP_PPC_EPR 130 
#define  KVM_CAP_PPC_OSI 129 
#define  KVM_CAP_PPC_PAPR 128 
 int kvmppc_sanity_check (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_vcpu_ioctl_enable_cap(struct kvm_vcpu *vcpu,
				     struct kvm_enable_cap *cap)
{
	int r;

	if (cap->flags)
		return -EINVAL;

	switch (cap->cap) {
	case KVM_CAP_PPC_OSI:
		r = 0;
		vcpu->arch.osi_enabled = true;
		break;
	case KVM_CAP_PPC_PAPR:
		r = 0;
		vcpu->arch.papr_enabled = true;
		break;
	case KVM_CAP_PPC_EPR:
		r = 0;
		if (cap->args[0])
			vcpu->arch.epr_flags |= KVMPPC_EPR_USER;
		else
			vcpu->arch.epr_flags &= ~KVMPPC_EPR_USER;
		break;
#ifdef CONFIG_BOOKE
	case KVM_CAP_PPC_BOOKE_WATCHDOG:
		r = 0;
		vcpu->arch.watchdog_enabled = true;
		break;
#endif
#if defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	case KVM_CAP_SW_TLB: {
		struct kvm_config_tlb cfg;
		void __user *user_ptr = (void __user *)(uintptr_t)cap->args[0];

		r = -EFAULT;
		if (copy_from_user(&cfg, user_ptr, sizeof(cfg)))
			break;

		r = kvm_vcpu_ioctl_config_tlb(vcpu, &cfg);
		break;
	}
#endif
#ifdef CONFIG_KVM_MPIC
	case KVM_CAP_IRQ_MPIC: {
		struct fd f;
		struct kvm_device *dev;

		r = -EBADF;
		f = fdget(cap->args[0]);
		if (!f.file)
			break;

		r = -EPERM;
		dev = kvm_device_from_filp(f.file);
		if (dev)
			r = kvmppc_mpic_connect_vcpu(dev, vcpu, cap->args[1]);

		fdput(f);
		break;
	}
#endif
#ifdef CONFIG_KVM_XICS
	case KVM_CAP_IRQ_XICS: {
		struct fd f;
		struct kvm_device *dev;

		r = -EBADF;
		f = fdget(cap->args[0]);
		if (!f.file)
			break;

		r = -EPERM;
		dev = kvm_device_from_filp(f.file);
		if (dev) {
			if (xive_enabled())
				r = kvmppc_xive_connect_vcpu(dev, vcpu, cap->args[1]);
			else
				r = kvmppc_xics_connect_vcpu(dev, vcpu, cap->args[1]);
		}

		fdput(f);
		break;
	}
#endif /* CONFIG_KVM_XICS */
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBLE
	case KVM_CAP_PPC_FWNMI:
		r = -EINVAL;
		if (!is_kvmppc_hv_enabled(vcpu->kvm))
			break;
		r = 0;
		vcpu->kvm->arch.fwnmi_enabled = true;
		break;
#endif /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */
	default:
		r = -EINVAL;
		break;
	}

	if (!r)
		r = kvmppc_sanity_check(vcpu);

	return r;
}