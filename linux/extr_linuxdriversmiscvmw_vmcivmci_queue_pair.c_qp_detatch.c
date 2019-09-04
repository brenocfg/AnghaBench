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
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int qp_detatch_guest_work (struct vmci_handle) ; 
 int qp_detatch_host_work (struct vmci_handle) ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 

__attribute__((used)) static int qp_detatch(struct vmci_handle handle, bool guest_endpoint)
{
	if (vmci_handle_is_invalid(handle))
		return VMCI_ERROR_INVALID_ARGS;

	if (guest_endpoint)
		return qp_detatch_guest_work(handle);
	else
		return qp_detatch_host_work(handle);
}