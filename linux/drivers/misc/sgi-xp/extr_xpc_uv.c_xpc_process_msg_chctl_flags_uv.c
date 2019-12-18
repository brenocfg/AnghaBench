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
struct xpc_partition {struct xpc_channel* channels; } ;
struct xpc_channel {int flags; } ;

/* Variables and functions */
 int XPC_C_CONNECTED ; 
 int XPC_C_CONNECTEDCALLOUT_MADE ; 
 int /*<<< orphan*/  xpc_activate_kthreads (struct xpc_channel*,int) ; 
 int /*<<< orphan*/  xpc_msgqueue_deref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_msgqueue_ref (struct xpc_channel*) ; 
 int xpc_n_of_deliverable_payloads_uv (struct xpc_channel*) ; 

__attribute__((used)) static void
xpc_process_msg_chctl_flags_uv(struct xpc_partition *part, int ch_number)
{
	struct xpc_channel *ch = &part->channels[ch_number];
	int ndeliverable_payloads;

	xpc_msgqueue_ref(ch);

	ndeliverable_payloads = xpc_n_of_deliverable_payloads_uv(ch);

	if (ndeliverable_payloads > 0 &&
	    (ch->flags & XPC_C_CONNECTED) &&
	    (ch->flags & XPC_C_CONNECTEDCALLOUT_MADE)) {

		xpc_activate_kthreads(ch, ndeliverable_payloads);
	}

	xpc_msgqueue_deref(ch);
}