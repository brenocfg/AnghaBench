#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmcb {int dummy; } ;
struct vcpu_svm {TYPE_2__* vmcb; int /*<<< orphan*/  vcpu; scalar_t__ next_rip; } ;
struct page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rax; } ;
struct TYPE_4__ {TYPE_1__ save; } ;

/* Variables and functions */
 scalar_t__ kvm_rip_read (int /*<<< orphan*/ *) ; 
 int kvm_skip_emulated_instruction (int /*<<< orphan*/ *) ; 
 scalar_t__ nested_svm_check_permissions (struct vcpu_svm*) ; 
 struct vmcb* nested_svm_map (struct vcpu_svm*,int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  nested_svm_unmap (struct page*) ; 
 int /*<<< orphan*/  nested_svm_vmloadsave (TYPE_2__*,struct vmcb*) ; 

__attribute__((used)) static int vmsave_interception(struct vcpu_svm *svm)
{
	struct vmcb *nested_vmcb;
	struct page *page;
	int ret;

	if (nested_svm_check_permissions(svm))
		return 1;

	nested_vmcb = nested_svm_map(svm, svm->vmcb->save.rax, &page);
	if (!nested_vmcb)
		return 1;

	svm->next_rip = kvm_rip_read(&svm->vcpu) + 3;
	ret = kvm_skip_emulated_instruction(&svm->vcpu);

	nested_svm_vmloadsave(svm->vmcb, nested_vmcb);
	nested_svm_unmap(page);

	return ret;
}