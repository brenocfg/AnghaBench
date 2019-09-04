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
struct kvm_vcpu {int dummy; } ;
struct kvm_run {int dummy; } ;
struct coproc_params {int dummy; } ;

/* Variables and functions */
 struct coproc_params decode_32bit_hsr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_skip_instr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_trap_il_is32bit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trap_raz_wi (struct kvm_vcpu*,struct coproc_params*,int /*<<< orphan*/ *) ; 

int kvm_handle_cp14_32(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	struct coproc_params params = decode_32bit_hsr(vcpu);

	/* raz_wi cp14 */
	trap_raz_wi(vcpu, &params, NULL);

	/* handled */
	kvm_skip_instr(vcpu, kvm_vcpu_trap_il_is32bit(vcpu));
	return 1;
}