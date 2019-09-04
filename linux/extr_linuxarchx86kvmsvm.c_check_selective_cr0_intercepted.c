#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct TYPE_8__ {unsigned long cr0; } ;
struct TYPE_10__ {TYPE_3__ arch; } ;
struct TYPE_9__ {unsigned long long intercept; } ;
struct vcpu_svm {TYPE_2__* vmcb; TYPE_5__ vcpu; TYPE_4__ nested; } ;
struct TYPE_6__ {int /*<<< orphan*/  exit_code; } ;
struct TYPE_7__ {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_SELECTIVE_CR0 ; 
 scalar_t__ NESTED_EXIT_DONE ; 
 unsigned long SVM_CR0_SELECTIVE_MASK ; 
 int /*<<< orphan*/  SVM_EXIT_CR0_SEL_WRITE ; 
 int /*<<< orphan*/  is_guest_mode (TYPE_5__*) ; 
 scalar_t__ nested_svm_exit_handled (struct vcpu_svm*) ; 

__attribute__((used)) static bool check_selective_cr0_intercepted(struct vcpu_svm *svm,
					    unsigned long val)
{
	unsigned long cr0 = svm->vcpu.arch.cr0;
	bool ret = false;
	u64 intercept;

	intercept = svm->nested.intercept;

	if (!is_guest_mode(&svm->vcpu) ||
	    (!(intercept & (1ULL << INTERCEPT_SELECTIVE_CR0))))
		return false;

	cr0 &= ~SVM_CR0_SELECTIVE_MASK;
	val &= ~SVM_CR0_SELECTIVE_MASK;

	if (cr0 ^ val) {
		svm->vmcb->control.exit_code = SVM_EXIT_CR0_SEL_WRITE;
		ret = (nested_svm_exit_handled(svm) == NESTED_EXIT_DONE);
	}

	return ret;
}