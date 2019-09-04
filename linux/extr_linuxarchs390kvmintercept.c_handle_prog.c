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
struct TYPE_5__ {TYPE_3__* sie_block; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit_program_interruption; } ;
struct kvm_vcpu {TYPE_2__ arch; TYPE_1__ stat; } ;
typedef  int /*<<< orphan*/  psw_t ;
struct TYPE_6__ {scalar_t__ iprcc; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ PGM_SPECIFICATION ; 
 int /*<<< orphan*/  __LC_PGM_NEW_PSW ; 
 scalar_t__ guestdbg_enabled (struct kvm_vcpu*) ; 
 int handle_itdb (struct kvm_vcpu*) ; 
 int inject_prog_on_prog_intercept (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_valid_psw (int /*<<< orphan*/ *) ; 
 int kvm_s390_handle_per_event (struct kvm_vcpu*) ; 
 scalar_t__ per_event (struct kvm_vcpu*) ; 
 int read_guest_lc (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_kvm_s390_intercept_prog (struct kvm_vcpu*,scalar_t__) ; 

__attribute__((used)) static int handle_prog(struct kvm_vcpu *vcpu)
{
	psw_t psw;
	int rc;

	vcpu->stat.exit_program_interruption++;

	if (guestdbg_enabled(vcpu) && per_event(vcpu)) {
		rc = kvm_s390_handle_per_event(vcpu);
		if (rc)
			return rc;
		/* the interrupt might have been filtered out completely */
		if (vcpu->arch.sie_block->iprcc == 0)
			return 0;
	}

	trace_kvm_s390_intercept_prog(vcpu, vcpu->arch.sie_block->iprcc);
	if (vcpu->arch.sie_block->iprcc == PGM_SPECIFICATION) {
		rc = read_guest_lc(vcpu, __LC_PGM_NEW_PSW, &psw, sizeof(psw_t));
		if (rc)
			return rc;
		/* Avoid endless loops of specification exceptions */
		if (!is_valid_psw(&psw))
			return -EOPNOTSUPP;
	}
	rc = handle_itdb(vcpu);
	if (rc)
		return rc;

	return inject_prog_on_prog_intercept(vcpu);
}