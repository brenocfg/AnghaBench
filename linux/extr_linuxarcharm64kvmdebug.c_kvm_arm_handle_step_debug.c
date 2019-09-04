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
struct kvm_vcpu {int guest_debug; } ;
struct TYPE_3__ {int hsr; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct kvm_run {TYPE_2__ debug; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int ESR_ELx_EC_SHIFT ; 
 int ESR_ELx_EC_SOFTSTP_LOW ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int KVM_GUESTDBG_SINGLESTEP ; 

bool kvm_arm_handle_step_debug(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	if (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP) {
		run->exit_reason = KVM_EXIT_DEBUG;
		run->debug.arch.hsr = ESR_ELx_EC_SOFTSTP_LOW << ESR_ELx_EC_SHIFT;
		return true;
	}
	return false;
}