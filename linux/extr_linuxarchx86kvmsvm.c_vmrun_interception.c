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
struct vcpu_svm {TYPE_2__* vmcb; int /*<<< orphan*/  vcpu; } ;
struct TYPE_3__ {scalar_t__ exit_info_2; scalar_t__ exit_info_1; scalar_t__ exit_code_hi; int /*<<< orphan*/  exit_code; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVM_EXIT_ERR ; 
 scalar_t__ kvm_rip_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_rip_write (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ nested_svm_check_permissions (struct vcpu_svm*) ; 
 int /*<<< orphan*/  nested_svm_vmexit (struct vcpu_svm*) ; 
 int /*<<< orphan*/  nested_svm_vmrun (struct vcpu_svm*) ; 
 int /*<<< orphan*/  nested_svm_vmrun_msrpm (struct vcpu_svm*) ; 

__attribute__((used)) static int vmrun_interception(struct vcpu_svm *svm)
{
	if (nested_svm_check_permissions(svm))
		return 1;

	/* Save rip after vmrun instruction */
	kvm_rip_write(&svm->vcpu, kvm_rip_read(&svm->vcpu) + 3);

	if (!nested_svm_vmrun(svm))
		return 1;

	if (!nested_svm_vmrun_msrpm(svm))
		goto failed;

	return 1;

failed:

	svm->vmcb->control.exit_code    = SVM_EXIT_ERR;
	svm->vmcb->control.exit_code_hi = 0;
	svm->vmcb->control.exit_info_1  = 0;
	svm->vmcb->control.exit_info_2  = 0;

	nested_svm_vmexit(svm);

	return 1;
}