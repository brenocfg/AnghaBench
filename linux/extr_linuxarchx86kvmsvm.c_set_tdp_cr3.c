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
struct vcpu_svm {TYPE_3__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cr3; } ;
struct TYPE_4__ {int /*<<< orphan*/  nested_cr3; } ;
struct TYPE_6__ {TYPE_2__ save; TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_CR ; 
 int /*<<< orphan*/  VMCB_NPT ; 
 int /*<<< orphan*/  __sme_set (unsigned long) ; 
 int /*<<< orphan*/  kvm_read_cr3 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mark_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void set_tdp_cr3(struct kvm_vcpu *vcpu, unsigned long root)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->control.nested_cr3 = __sme_set(root);
	mark_dirty(svm->vmcb, VMCB_NPT);

	/* Also sync guest cr3 here in case we live migrate */
	svm->vmcb->save.cr3 = kvm_read_cr3(vcpu);
	mark_dirty(svm->vmcb, VMCB_CR);
}