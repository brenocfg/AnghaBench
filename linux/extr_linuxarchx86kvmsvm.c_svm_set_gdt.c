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
struct desc_ptr {int /*<<< orphan*/  address; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; } ;
struct TYPE_5__ {TYPE_1__ gdtr; } ;
struct TYPE_6__ {TYPE_2__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_DT ; 
 int /*<<< orphan*/  mark_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_set_gdt(struct kvm_vcpu *vcpu, struct desc_ptr *dt)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->save.gdtr.limit = dt->size;
	svm->vmcb->save.gdtr.base = dt->address ;
	mark_dirty(svm->vmcb, VMCB_DT);
}