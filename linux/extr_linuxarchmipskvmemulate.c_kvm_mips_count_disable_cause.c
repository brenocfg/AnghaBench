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
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {int count_ctl; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAUSEF_DC ; 
 int KVM_REG_MIPS_COUNT_CTL_DC ; 
 int /*<<< orphan*/  kvm_mips_count_disable (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_set_c0_guest_cause (struct mips_coproc*,int /*<<< orphan*/ ) ; 

void kvm_mips_count_disable_cause(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;

	kvm_set_c0_guest_cause(cop0, CAUSEF_DC);
	if (!(vcpu->arch.count_ctl & KVM_REG_MIPS_COUNT_CTL_DC))
		kvm_mips_count_disable(vcpu);
}