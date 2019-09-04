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
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_HAS_RAS_EXTN ; 
#define  KVM_CAP_ARM_EL1_32BIT 135 
#define  KVM_CAP_ARM_INJECT_SERROR_ESR 134 
#define  KVM_CAP_ARM_PMU_V3 133 
#define  KVM_CAP_GUEST_DEBUG_HW_BPS 132 
#define  KVM_CAP_GUEST_DEBUG_HW_WPS 131 
#define  KVM_CAP_SET_GUEST_DEBUG 130 
#define  KVM_CAP_VCPU_ATTRIBUTES 129 
#define  KVM_CAP_VCPU_EVENTS 128 
 int cpu_has_32bit_el1 () ; 
 int cpus_have_const_cap (int /*<<< orphan*/ ) ; 
 int get_num_brps () ; 
 int get_num_wrps () ; 
 int kvm_arm_support_pmu_v3 () ; 

int kvm_arch_dev_ioctl_check_extension(struct kvm *kvm, long ext)
{
	int r;

	switch (ext) {
	case KVM_CAP_ARM_EL1_32BIT:
		r = cpu_has_32bit_el1();
		break;
	case KVM_CAP_GUEST_DEBUG_HW_BPS:
		r = get_num_brps();
		break;
	case KVM_CAP_GUEST_DEBUG_HW_WPS:
		r = get_num_wrps();
		break;
	case KVM_CAP_ARM_PMU_V3:
		r = kvm_arm_support_pmu_v3();
		break;
	case KVM_CAP_ARM_INJECT_SERROR_ESR:
		r = cpus_have_const_cap(ARM64_HAS_RAS_EXTN);
		break;
	case KVM_CAP_SET_GUEST_DEBUG:
	case KVM_CAP_VCPU_ATTRIBUTES:
	case KVM_CAP_VCPU_EVENTS:
		r = 1;
		break;
	default:
		r = 0;
	}

	return r;
}