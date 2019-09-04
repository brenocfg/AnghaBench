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
struct TYPE_6__ {TYPE_2__* sie_block; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit_io_request; int /*<<< orphan*/  exit_external_request; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_1__ stat; int /*<<< orphan*/  kvm; } ;
struct TYPE_5__ {int icptcode; int icptstatus; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ICPT_EXTINT 138 
#define  ICPT_EXTREQ 137 
#define  ICPT_INST 136 
#define  ICPT_IOREQ 135 
#define  ICPT_KSS 134 
#define  ICPT_OPEREXC 133 
#define  ICPT_PARTEXEC 132 
#define  ICPT_PROGI 131 
#define  ICPT_STOP 130 
#define  ICPT_VALIDITY 129 
#define  ICPT_WAIT 128 
 int handle_external_interrupt (struct kvm_vcpu*) ; 
 int handle_instruction (struct kvm_vcpu*) ; 
 int handle_operexc (struct kvm_vcpu*) ; 
 int handle_partial_execution (struct kvm_vcpu*) ; 
 int handle_prog (struct kvm_vcpu*) ; 
 int handle_stop (struct kvm_vcpu*) ; 
 int handle_validity (struct kvm_vcpu*) ; 
 scalar_t__ kvm_is_ucontrol (int /*<<< orphan*/ ) ; 
 int kvm_s390_handle_per_ifetch_icpt (struct kvm_vcpu*) ; 
 int kvm_s390_handle_wait (struct kvm_vcpu*) ; 
 int kvm_s390_skey_check_enable (struct kvm_vcpu*) ; 

int kvm_handle_sie_intercept(struct kvm_vcpu *vcpu)
{
	int rc, per_rc = 0;

	if (kvm_is_ucontrol(vcpu->kvm))
		return -EOPNOTSUPP;

	switch (vcpu->arch.sie_block->icptcode) {
	case ICPT_EXTREQ:
		vcpu->stat.exit_external_request++;
		return 0;
	case ICPT_IOREQ:
		vcpu->stat.exit_io_request++;
		return 0;
	case ICPT_INST:
		rc = handle_instruction(vcpu);
		break;
	case ICPT_PROGI:
		return handle_prog(vcpu);
	case ICPT_EXTINT:
		return handle_external_interrupt(vcpu);
	case ICPT_WAIT:
		return kvm_s390_handle_wait(vcpu);
	case ICPT_VALIDITY:
		return handle_validity(vcpu);
	case ICPT_STOP:
		return handle_stop(vcpu);
	case ICPT_OPEREXC:
		rc = handle_operexc(vcpu);
		break;
	case ICPT_PARTEXEC:
		rc = handle_partial_execution(vcpu);
		break;
	case ICPT_KSS:
		rc = kvm_s390_skey_check_enable(vcpu);
		break;
	default:
		return -EOPNOTSUPP;
	}

	/* process PER, also if the instrution is processed in user space */
	if (vcpu->arch.sie_block->icptstatus & 0x02 &&
	    (!rc || rc == -EOPNOTSUPP))
		per_rc = kvm_s390_handle_per_ifetch_icpt(vcpu);
	return per_rc ? per_rc : rc;
}