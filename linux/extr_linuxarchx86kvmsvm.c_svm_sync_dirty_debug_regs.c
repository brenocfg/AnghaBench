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
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct TYPE_6__ {int /*<<< orphan*/  switch_db_regs; int /*<<< orphan*/  dr7; int /*<<< orphan*/  dr6; int /*<<< orphan*/ * db; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  dr7; } ;
struct TYPE_5__ {TYPE_1__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_DEBUGREG_WONT_EXIT ; 
 int /*<<< orphan*/  get_debugreg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dr_intercepts (struct vcpu_svm*) ; 
 int /*<<< orphan*/  svm_get_dr6 (struct kvm_vcpu*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_sync_dirty_debug_regs(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	get_debugreg(vcpu->arch.db[0], 0);
	get_debugreg(vcpu->arch.db[1], 1);
	get_debugreg(vcpu->arch.db[2], 2);
	get_debugreg(vcpu->arch.db[3], 3);
	vcpu->arch.dr6 = svm_get_dr6(vcpu);
	vcpu->arch.dr7 = svm->vmcb->save.dr7;

	vcpu->arch.switch_db_regs &= ~KVM_DEBUGREG_WONT_EXIT;
	set_dr_intercepts(svm);
}