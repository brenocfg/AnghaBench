#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nr_hw_wp; scalar_t__ nr_hw_bp; struct kvm_hw_wp_info_arch* hw_bp_info; struct kvm_hw_wp_info_arch* hw_wp_info; } ;
struct TYPE_4__ {TYPE_1__ guestdbg; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_hw_wp_info_arch {struct kvm_hw_wp_info_arch* old_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct kvm_hw_wp_info_arch*) ; 

void kvm_s390_clear_bp_data(struct kvm_vcpu *vcpu)
{
	int i;
	struct kvm_hw_wp_info_arch *hw_wp_info = NULL;

	for (i = 0; i < vcpu->arch.guestdbg.nr_hw_wp; i++) {
		hw_wp_info = &vcpu->arch.guestdbg.hw_wp_info[i];
		kfree(hw_wp_info->old_data);
		hw_wp_info->old_data = NULL;
	}
	kfree(vcpu->arch.guestdbg.hw_wp_info);
	vcpu->arch.guestdbg.hw_wp_info = NULL;

	kfree(vcpu->arch.guestdbg.hw_bp_info);
	vcpu->arch.guestdbg.hw_bp_info = NULL;

	vcpu->arch.guestdbg.nr_hw_wp = 0;
	vcpu->arch.guestdbg.nr_hw_bp = 0;
}