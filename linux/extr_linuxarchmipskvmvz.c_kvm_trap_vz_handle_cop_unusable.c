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
typedef  int u32 ;
struct TYPE_2__ {int host_cp0_cause; int aux_inuse; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm_run* run; } ;
struct kvm_run {int /*<<< orphan*/  exit_reason; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int CAUSEB_CE ; 
 int CAUSEF_CE ; 
#define  EMULATE_DONE 129 
#define  EMULATE_FAIL 128 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int KVM_MIPS_AUX_FPU ; 
 int RESUME_GUEST ; 
 int RESUME_HOST ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kvm_mips_guest_has_fpu (TYPE_1__*) ; 
 int /*<<< orphan*/  kvm_own_fpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int kvm_trap_vz_handle_cop_unusable(struct kvm_vcpu *vcpu)
{
	struct kvm_run *run = vcpu->run;
	u32 cause = vcpu->arch.host_cp0_cause;
	enum emulation_result er = EMULATE_FAIL;
	int ret = RESUME_GUEST;

	if (((cause & CAUSEF_CE) >> CAUSEB_CE) == 1) {
		/*
		 * If guest FPU not present, the FPU operation should have been
		 * treated as a reserved instruction!
		 * If FPU already in use, we shouldn't get this at all.
		 */
		if (WARN_ON(!kvm_mips_guest_has_fpu(&vcpu->arch) ||
			    vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU)) {
			preempt_enable();
			return EMULATE_FAIL;
		}

		kvm_own_fpu(vcpu);
		er = EMULATE_DONE;
	}
	/* other coprocessors not handled */

	switch (er) {
	case EMULATE_DONE:
		ret = RESUME_GUEST;
		break;

	case EMULATE_FAIL:
		run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = RESUME_HOST;
		break;

	default:
		BUG();
	}
	return ret;
}