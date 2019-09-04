#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vmci_handle {int dummy; } ;
struct TYPE_8__ {int payload_size; void* src; void* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_7__ {TYPE_4__ hdr; TYPE_1__ event_data; } ;
struct TYPE_6__ {scalar_t__ peer_id; struct vmci_handle handle; } ;
struct vmci_event_qp {TYPE_3__ msg; TYPE_2__ payload; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_CONTEXT_RESOURCE_ID ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  VMCI_EVENT_HANDLER ; 
 int /*<<< orphan*/  VMCI_EVENT_QP_PEER_ATTACH ; 
 int /*<<< orphan*/  VMCI_EVENT_QP_PEER_DETACH ; 
 scalar_t__ VMCI_HYPERVISOR_CONTEXT_ID ; 
 scalar_t__ VMCI_INVALID_ID ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  pr_warn (char*,char*,scalar_t__) ; 
 int vmci_datagram_dispatch (scalar_t__,TYPE_4__*,int) ; 
 scalar_t__ vmci_handle_is_invalid (struct vmci_handle) ; 
 void* vmci_make_handle (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qp_notify_peer(bool attach,
			  struct vmci_handle handle,
			  u32 my_id,
			  u32 peer_id)
{
	int rv;
	struct vmci_event_qp ev;

	if (vmci_handle_is_invalid(handle) || my_id == VMCI_INVALID_ID ||
	    peer_id == VMCI_INVALID_ID)
		return VMCI_ERROR_INVALID_ARGS;

	/*
	 * In vmci_ctx_enqueue_datagram() we enforce the upper limit on
	 * number of pending events from the hypervisor to a given VM
	 * otherwise a rogue VM could do an arbitrary number of attach
	 * and detach operations causing memory pressure in the host
	 * kernel.
	 */

	ev.msg.hdr.dst = vmci_make_handle(peer_id, VMCI_EVENT_HANDLER);
	ev.msg.hdr.src = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					  VMCI_CONTEXT_RESOURCE_ID);
	ev.msg.hdr.payload_size = sizeof(ev) - sizeof(ev.msg.hdr);
	ev.msg.event_data.event = attach ?
	    VMCI_EVENT_QP_PEER_ATTACH : VMCI_EVENT_QP_PEER_DETACH;
	ev.payload.handle = handle;
	ev.payload.peer_id = my_id;

	rv = vmci_datagram_dispatch(VMCI_HYPERVISOR_CONTEXT_ID,
				    &ev.msg.hdr, false);
	if (rv < VMCI_SUCCESS)
		pr_warn("Failed to enqueue queue_pair %s event datagram for context (ID=0x%x)\n",
			attach ? "ATTACH" : "DETACH", peer_id);

	return rv;
}