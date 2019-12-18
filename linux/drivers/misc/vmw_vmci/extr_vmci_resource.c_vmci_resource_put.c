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
struct vmci_resource {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int VMCI_SUCCESS ; 
 int VMCI_SUCCESS_ENTRY_DEAD ; 
 scalar_t__ kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_release_resource ; 

int vmci_resource_put(struct vmci_resource *resource)
{
	/*
	 * We propagate the information back to caller in case it wants to know
	 * whether entry was freed.
	 */
	return kref_put(&resource->kref, vmci_release_resource) ?
		VMCI_SUCCESS_ENTRY_DEAD : VMCI_SUCCESS;
}