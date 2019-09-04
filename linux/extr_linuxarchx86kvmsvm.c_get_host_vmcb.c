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
struct vmcb {int dummy; } ;
struct TYPE_2__ {struct vmcb* hsave; } ;
struct vcpu_svm {struct vmcb* vmcb; TYPE_1__ nested; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 scalar_t__ is_guest_mode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct vmcb *get_host_vmcb(struct vcpu_svm *svm)
{
	if (is_guest_mode(&svm->vcpu))
		return svm->nested.hsave;
	else
		return svm->vmcb;
}