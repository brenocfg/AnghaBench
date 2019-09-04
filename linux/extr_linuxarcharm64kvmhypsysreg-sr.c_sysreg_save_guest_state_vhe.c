#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_cpu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sysreg_save_common_state (struct kvm_cpu_context*) ; 
 int /*<<< orphan*/  __sysreg_save_el2_return_state (struct kvm_cpu_context*) ; 

void sysreg_save_guest_state_vhe(struct kvm_cpu_context *ctxt)
{
	__sysreg_save_common_state(ctxt);
	__sysreg_save_el2_return_state(ctxt);
}