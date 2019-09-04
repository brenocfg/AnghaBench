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
struct TYPE_6__ {unsigned long long intercept; int exit_required; } ;
struct vcpu_svm {TYPE_3__ nested; TYPE_2__* vmcb; int /*<<< orphan*/  vcpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit_code; } ;
struct TYPE_5__ {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_NMI ; 
 int /*<<< orphan*/  SVM_EXIT_NMI ; 
 int /*<<< orphan*/  is_guest_mode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool nested_svm_nmi(struct vcpu_svm *svm)
{
	if (!is_guest_mode(&svm->vcpu))
		return true;

	if (!(svm->nested.intercept & (1ULL << INTERCEPT_NMI)))
		return true;

	svm->vmcb->control.exit_code = SVM_EXIT_NMI;
	svm->nested.exit_required = true;

	return false;
}