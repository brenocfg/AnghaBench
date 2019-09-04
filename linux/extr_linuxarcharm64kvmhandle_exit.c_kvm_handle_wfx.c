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
struct TYPE_2__ {int /*<<< orphan*/  wfi_exit_stat; int /*<<< orphan*/  wfe_exit_stat; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int ESR_ELx_WFx_ISS_WFE ; 
 int /*<<< orphan*/  KVM_REQ_UNHALT ; 
 int /*<<< orphan*/  kvm_clear_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_skip_instr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_block (struct kvm_vcpu*) ; 
 int kvm_vcpu_get_hsr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_on_spin (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_trap_il_is32bit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_wfx_arm64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcpu_mode_priv (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_handle_wfx(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	if (kvm_vcpu_get_hsr(vcpu) & ESR_ELx_WFx_ISS_WFE) {
		trace_kvm_wfx_arm64(*vcpu_pc(vcpu), true);
		vcpu->stat.wfe_exit_stat++;
		kvm_vcpu_on_spin(vcpu, vcpu_mode_priv(vcpu));
	} else {
		trace_kvm_wfx_arm64(*vcpu_pc(vcpu), false);
		vcpu->stat.wfi_exit_stat++;
		kvm_vcpu_block(vcpu);
		kvm_clear_request(KVM_REQ_UNHALT, vcpu);
	}

	kvm_skip_instr(vcpu, kvm_vcpu_trap_il_is32bit(vcpu));

	return 1;
}