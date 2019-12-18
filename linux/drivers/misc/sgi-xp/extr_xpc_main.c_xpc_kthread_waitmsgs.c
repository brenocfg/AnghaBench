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
struct xpc_partition {int dummy; } ;
struct xpc_channel {int flags; scalar_t__ kthreads_idle_limit; int /*<<< orphan*/  kthreads_idle; int /*<<< orphan*/  idle_wq; } ;
struct TYPE_2__ {int (* n_of_deliverable_payloads ) (struct xpc_channel*) ;} ;

/* Variables and functions */
 int XPC_C_DISCONNECTING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wait_event_interruptible_exclusive (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_deliver_payload (struct xpc_channel*) ; 

__attribute__((used)) static void
xpc_kthread_waitmsgs(struct xpc_partition *part, struct xpc_channel *ch)
{
	int (*n_of_deliverable_payloads) (struct xpc_channel *) =
		xpc_arch_ops.n_of_deliverable_payloads;

	do {
		/* deliver messages to their intended recipients */

		while (n_of_deliverable_payloads(ch) > 0 &&
		       !(ch->flags & XPC_C_DISCONNECTING)) {
			xpc_deliver_payload(ch);
		}

		if (atomic_inc_return(&ch->kthreads_idle) >
		    ch->kthreads_idle_limit) {
			/* too many idle kthreads on this channel */
			atomic_dec(&ch->kthreads_idle);
			break;
		}

		dev_dbg(xpc_chan, "idle kthread calling "
			"wait_event_interruptible_exclusive()\n");

		(void)wait_event_interruptible_exclusive(ch->idle_wq,
				(n_of_deliverable_payloads(ch) > 0 ||
				 (ch->flags & XPC_C_DISCONNECTING)));

		atomic_dec(&ch->kthreads_idle);

	} while (!(ch->flags & XPC_C_DISCONNECTING));
}