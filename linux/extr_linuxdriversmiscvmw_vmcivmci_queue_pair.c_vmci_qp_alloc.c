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
typedef  int /*<<< orphan*/  vmci_event_release_cb ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct vmci_queue {int dummy; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_QP_ALL_FLAGS ; 
 int qp_alloc_guest_work (struct vmci_handle*,struct vmci_queue**,int /*<<< orphan*/ ,struct vmci_queue**,int /*<<< orphan*/ ,int,int,int) ; 
 int qp_alloc_host_work (struct vmci_handle*,struct vmci_queue**,int /*<<< orphan*/ ,struct vmci_queue**,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,void*) ; 

int vmci_qp_alloc(struct vmci_handle *handle,
		  struct vmci_queue **produce_q,
		  u64 produce_size,
		  struct vmci_queue **consume_q,
		  u64 consume_size,
		  u32 peer,
		  u32 flags,
		  u32 priv_flags,
		  bool guest_endpoint,
		  vmci_event_release_cb wakeup_cb,
		  void *client_data)
{
	if (!handle || !produce_q || !consume_q ||
	    (!produce_size && !consume_size) || (flags & ~VMCI_QP_ALL_FLAGS))
		return VMCI_ERROR_INVALID_ARGS;

	if (guest_endpoint) {
		return qp_alloc_guest_work(handle, produce_q,
					   produce_size, consume_q,
					   consume_size, peer,
					   flags, priv_flags);
	} else {
		return qp_alloc_host_work(handle, produce_q,
					  produce_size, consume_q,
					  consume_size, peer, flags,
					  priv_flags, wakeup_cb, client_data);
	}
}