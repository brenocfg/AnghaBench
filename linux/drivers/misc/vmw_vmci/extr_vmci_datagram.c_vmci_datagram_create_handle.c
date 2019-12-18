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
typedef  int /*<<< orphan*/  vmci_datagram_recv_cb ;
typedef  int /*<<< orphan*/  u32 ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_DEFAULT_PROC_PRIVILEGE_FLAGS ; 
 int vmci_datagram_create_handle_priv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct vmci_handle*) ; 

int vmci_datagram_create_handle(u32 resource_id,
				u32 flags,
				vmci_datagram_recv_cb recv_cb,
				void *client_data,
				struct vmci_handle *out_handle)
{
	return vmci_datagram_create_handle_priv(
		resource_id, flags,
		VMCI_DEFAULT_PROC_PRIVILEGE_FLAGS,
		recv_cb, client_data,
		out_handle);
}