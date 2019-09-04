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
struct TYPE_5__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  guest_debug; } ;
struct TYPE_6__ {int as; } ;
struct TYPE_4__ {scalar_t__ iprcc; int /*<<< orphan*/  gpsw; int /*<<< orphan*/  peraddr; int /*<<< orphan*/  perc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_GUESTDBG_EXIT_PENDING ; 
 scalar_t__ PGM_SPACE_SWITCH ; 
 int PSW_BITS_AS_HOME ; 
 int PSW_BITS_AS_PRIMARY ; 
 scalar_t__ debug_exit_required (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int filter_guest_per_event (struct kvm_vcpu*) ; 
 scalar_t__ hssec (struct kvm_vcpu*) ; 
 int old_as_is_home (struct kvm_vcpu*) ; 
 scalar_t__ old_ssec (struct kvm_vcpu*) ; 
 scalar_t__ pssec (struct kvm_vcpu*) ; 
 TYPE_3__ psw_bits (int /*<<< orphan*/ ) ; 

int kvm_s390_handle_per_event(struct kvm_vcpu *vcpu)
{
	int rc, new_as;

	if (debug_exit_required(vcpu, vcpu->arch.sie_block->perc,
				vcpu->arch.sie_block->peraddr))
		vcpu->guest_debug |= KVM_GUESTDBG_EXIT_PENDING;

	rc = filter_guest_per_event(vcpu);
	if (rc)
		return rc;

	/*
	 * Only RP, SAC, SACF, PT, PTI, PR, PC instructions can trigger
	 * a space-switch event. PER events enforce space-switch events
	 * for these instructions. So if no PER event for the guest is left,
	 * we might have to filter the space-switch element out, too.
	 */
	if (vcpu->arch.sie_block->iprcc == PGM_SPACE_SWITCH) {
		vcpu->arch.sie_block->iprcc = 0;
		new_as = psw_bits(vcpu->arch.sie_block->gpsw).as;

		/*
		 * If the AS changed from / to home, we had RP, SAC or SACF
		 * instruction. Check primary and home space-switch-event
		 * controls. (theoretically home -> home produced no event)
		 */
		if (((new_as == PSW_BITS_AS_HOME) ^ old_as_is_home(vcpu)) &&
		    (pssec(vcpu) || hssec(vcpu)))
			vcpu->arch.sie_block->iprcc = PGM_SPACE_SWITCH;

		/*
		 * PT, PTI, PR, PC instruction operate on primary AS only. Check
		 * if the primary-space-switch-event control was or got set.
		 */
		if (new_as == PSW_BITS_AS_PRIMARY && !old_as_is_home(vcpu) &&
		    (pssec(vcpu) || old_ssec(vcpu)))
			vcpu->arch.sie_block->iprcc = PGM_SPACE_SWITCH;
	}
	return 0;
}