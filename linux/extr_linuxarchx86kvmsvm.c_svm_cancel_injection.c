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
struct vmcb_control_area {scalar_t__ event_inj; int /*<<< orphan*/  event_inj_err; int /*<<< orphan*/  exit_int_info_err; scalar_t__ exit_int_info; } ;
struct vcpu_svm {TYPE_1__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {struct vmcb_control_area control; } ;

/* Variables and functions */
 int /*<<< orphan*/  svm_complete_interrupts (struct vcpu_svm*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_cancel_injection(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	struct vmcb_control_area *control = &svm->vmcb->control;

	control->exit_int_info = control->event_inj;
	control->exit_int_info_err = control->event_inj_err;
	control->event_inj = 0;
	svm_complete_interrupts(svm);
}