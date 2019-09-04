#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dr6; int /*<<< orphan*/  singlestep_rip; } ;
struct kvm_vcpu {int guest_debug; TYPE_3__ arch; struct kvm_run* run; } ;
struct TYPE_4__ {int dr6; int /*<<< orphan*/  exception; int /*<<< orphan*/  pc; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;
struct kvm_run {int /*<<< orphan*/  exit_reason; TYPE_2__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_VECTOR ; 
 int DR6_BS ; 
 int DR6_FIXED_1 ; 
 int DR6_RTM ; 
 int EMULATE_USER_EXIT ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vcpu_do_singlestep(struct kvm_vcpu *vcpu, int *r)
{
	struct kvm_run *kvm_run = vcpu->run;

	if (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP) {
		kvm_run->debug.arch.dr6 = DR6_BS | DR6_FIXED_1 | DR6_RTM;
		kvm_run->debug.arch.pc = vcpu->arch.singlestep_rip;
		kvm_run->debug.arch.exception = DB_VECTOR;
		kvm_run->exit_reason = KVM_EXIT_DEBUG;
		*r = EMULATE_USER_EXIT;
	} else {
		/*
		 * "Certain debug exceptions may clear bit 0-3.  The
		 * remaining contents of the DR6 register are never
		 * cleared by the processor".
		 */
		vcpu->arch.dr6 &= ~15;
		vcpu->arch.dr6 |= DR6_BS | DR6_RTM;
		kvm_queue_exception(vcpu, DB_VECTOR);
	}
}