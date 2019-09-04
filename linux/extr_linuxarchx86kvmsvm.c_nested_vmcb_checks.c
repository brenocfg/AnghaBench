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
struct TYPE_2__ {unsigned long long intercept; scalar_t__ asid; int nested_ctl; } ;
struct vmcb {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_VMRUN ; 
 int SVM_NESTED_CTL_NP_ENABLE ; 
 int /*<<< orphan*/  npt_enabled ; 

__attribute__((used)) static bool nested_vmcb_checks(struct vmcb *vmcb)
{
	if ((vmcb->control.intercept & (1ULL << INTERCEPT_VMRUN)) == 0)
		return false;

	if (vmcb->control.asid == 0)
		return false;

	if ((vmcb->control.nested_ctl & SVM_NESTED_CTL_NP_ENABLE) &&
	    !npt_enabled)
		return false;

	return true;
}