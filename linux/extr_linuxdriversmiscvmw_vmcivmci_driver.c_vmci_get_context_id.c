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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_HOST_CONTEXT_ID ; 
 int /*<<< orphan*/  VMCI_INVALID_ID ; 
 int /*<<< orphan*/  vmci_get_vm_context_id () ; 
 scalar_t__ vmci_guest_code_active () ; 
 scalar_t__ vmci_host_code_active () ; 

u32 vmci_get_context_id(void)
{
	if (vmci_guest_code_active())
		return vmci_get_vm_context_id();
	else if (vmci_host_code_active())
		return VMCI_HOST_CONTEXT_ID;

	return VMCI_INVALID_ID;
}