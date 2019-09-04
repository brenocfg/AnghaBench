#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int exit_required; unsigned long long intercept; } ;
struct TYPE_7__ {int hflags; } ;
struct TYPE_12__ {TYPE_1__ arch; } ;
struct vcpu_svm {TYPE_5__* vmcb; TYPE_3__ nested; TYPE_6__ vcpu; } ;
struct TYPE_10__ {int /*<<< orphan*/  rip; } ;
struct TYPE_8__ {scalar_t__ exit_info_2; scalar_t__ exit_info_1; int /*<<< orphan*/  exit_code; } ;
struct TYPE_11__ {TYPE_4__ save; TYPE_2__ control; } ;

/* Variables and functions */
 int HF_HIF_MASK ; 
 int HF_VINTR_MASK ; 
 int /*<<< orphan*/  SVM_EXIT_INTR ; 
 int /*<<< orphan*/  is_guest_mode (TYPE_6__*) ; 
 int /*<<< orphan*/  trace_kvm_nested_intr_vmexit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool nested_svm_intr(struct vcpu_svm *svm)
{
	if (!is_guest_mode(&svm->vcpu))
		return true;

	if (!(svm->vcpu.arch.hflags & HF_VINTR_MASK))
		return true;

	if (!(svm->vcpu.arch.hflags & HF_HIF_MASK))
		return false;

	/*
	 * if vmexit was already requested (by intercepted exception
	 * for instance) do not overwrite it with "external interrupt"
	 * vmexit.
	 */
	if (svm->nested.exit_required)
		return false;

	svm->vmcb->control.exit_code   = SVM_EXIT_INTR;
	svm->vmcb->control.exit_info_1 = 0;
	svm->vmcb->control.exit_info_2 = 0;

	if (svm->nested.intercept & 1ULL) {
		/*
		 * The #vmexit can't be emulated here directly because this
		 * code path runs with irqs and preemption disabled. A
		 * #vmexit emulation might sleep. Only signal request for
		 * the #vmexit here.
		 */
		svm->nested.exit_required = true;
		trace_kvm_nested_intr_vmexit(svm->vmcb->save.rip);
		return false;
	}

	return true;
}