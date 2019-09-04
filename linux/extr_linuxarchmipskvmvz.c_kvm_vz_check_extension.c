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
#define  KVM_CAP_MIPS_VZ 128 

__attribute__((used)) static int kvm_vz_check_extension(struct kvm *kvm, long ext)
{
	int r;

	switch (ext) {
	case KVM_CAP_MIPS_VZ:
		/* we wouldn't be here unless cpu_has_vz */
		r = 1;
		break;
#ifdef CONFIG_64BIT
	case KVM_CAP_MIPS_64BIT:
		/* We support 64-bit registers/operations and addresses */
		r = 2;
		break;
#endif
	default:
		r = 0;
		break;
	}

	return r;
}