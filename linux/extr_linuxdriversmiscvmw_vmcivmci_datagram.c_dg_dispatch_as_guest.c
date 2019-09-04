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
struct vmci_resource {int dummy; } ;
struct vmci_datagram {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int VMCI_ERROR_NO_HANDLE ; 
 int /*<<< orphan*/  VMCI_RESOURCE_TYPE_DATAGRAM ; 
 struct vmci_resource* vmci_resource_by_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_resource_put (struct vmci_resource*) ; 
 int vmci_send_datagram (struct vmci_datagram*) ; 

__attribute__((used)) static int dg_dispatch_as_guest(struct vmci_datagram *dg)
{
	int retval;
	struct vmci_resource *resource;

	resource = vmci_resource_by_handle(dg->src,
					   VMCI_RESOURCE_TYPE_DATAGRAM);
	if (!resource)
		return VMCI_ERROR_NO_HANDLE;

	retval = vmci_send_datagram(dg);
	vmci_resource_put(resource);
	return retval;
}