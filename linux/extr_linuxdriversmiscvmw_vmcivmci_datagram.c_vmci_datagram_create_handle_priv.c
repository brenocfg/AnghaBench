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
typedef  int /*<<< orphan*/ * vmci_datagram_recv_cb ;
typedef  int u32 ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_PRIVILEGE_ALL_FLAGS ; 
 int dg_create_handle (int,int,int,int /*<<< orphan*/ *,void*,struct vmci_handle*) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 

int vmci_datagram_create_handle_priv(u32 resource_id,
				     u32 flags,
				     u32 priv_flags,
				     vmci_datagram_recv_cb recv_cb,
				     void *client_data,
				     struct vmci_handle *out_handle)
{
	if (out_handle == NULL)
		return VMCI_ERROR_INVALID_ARGS;

	if (recv_cb == NULL) {
		pr_devel("Client callback needed when creating datagram\n");
		return VMCI_ERROR_INVALID_ARGS;
	}

	if (priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS)
		return VMCI_ERROR_INVALID_ARGS;

	return dg_create_handle(resource_id, flags, priv_flags, recv_cb,
				client_data, out_handle);
}