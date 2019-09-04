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
struct TYPE_4__ {TYPE_1__* debug_ptr; } ;
struct kvm_vcpu {int guest_debug; TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dbg_wvr; int /*<<< orphan*/ * dbg_wcr; int /*<<< orphan*/ * dbg_bvr; int /*<<< orphan*/ * dbg_bcr; } ;

/* Variables and functions */
 int KVM_GUESTDBG_USE_HW ; 
 int /*<<< orphan*/  get_num_brps () ; 
 int /*<<< orphan*/  get_num_wrps () ; 
 int /*<<< orphan*/  kvm_arm_reset_debug_ptr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  restore_guest_debug_regs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_arm_clear_debug (int) ; 
 int /*<<< orphan*/  trace_kvm_arm_set_regset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void kvm_arm_clear_debug(struct kvm_vcpu *vcpu)
{
	trace_kvm_arm_clear_debug(vcpu->guest_debug);

	if (vcpu->guest_debug) {
		restore_guest_debug_regs(vcpu);

		/*
		 * If we were using HW debug we need to restore the
		 * debug_ptr to the guest debug state.
		 */
		if (vcpu->guest_debug & KVM_GUESTDBG_USE_HW) {
			kvm_arm_reset_debug_ptr(vcpu);

			trace_kvm_arm_set_regset("BKPTS", get_num_brps(),
						&vcpu->arch.debug_ptr->dbg_bcr[0],
						&vcpu->arch.debug_ptr->dbg_bvr[0]);

			trace_kvm_arm_set_regset("WAPTS", get_num_wrps(),
						&vcpu->arch.debug_ptr->dbg_wcr[0],
						&vcpu->arch.debug_ptr->dbg_wvr[0]);
		}
	}
}