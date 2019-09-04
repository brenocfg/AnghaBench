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
struct TYPE_2__ {int vmexit_ctrl; int vmentry_ctrl; } ;

/* Variables and functions */
 int VM_ENTRY_LOAD_BNDCFGS ; 
 int VM_EXIT_CLEAR_BNDCFGS ; 
 TYPE_1__ vmcs_config ; 

__attribute__((used)) static bool vmx_mpx_supported(void)
{
	return (vmcs_config.vmexit_ctrl & VM_EXIT_CLEAR_BNDCFGS) &&
		(vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_BNDCFGS);
}