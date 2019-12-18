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
struct xpc_channel {int kthreads_assigned_limit; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; int /*<<< orphan*/  idle_wq; int /*<<< orphan*/  kthreads_assigned; int /*<<< orphan*/  kthreads_idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_nr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_create_kthreads (struct xpc_channel*,int,int /*<<< orphan*/ ) ; 

void
xpc_activate_kthreads(struct xpc_channel *ch, int needed)
{
	int idle = atomic_read(&ch->kthreads_idle);
	int assigned = atomic_read(&ch->kthreads_assigned);
	int wakeup;

	DBUG_ON(needed <= 0);

	if (idle > 0) {
		wakeup = (needed > idle) ? idle : needed;
		needed -= wakeup;

		dev_dbg(xpc_chan, "wakeup %d idle kthreads, partid=%d, "
			"channel=%d\n", wakeup, ch->partid, ch->number);

		/* only wakeup the requested number of kthreads */
		wake_up_nr(&ch->idle_wq, wakeup);
	}

	if (needed <= 0)
		return;

	if (needed + assigned > ch->kthreads_assigned_limit) {
		needed = ch->kthreads_assigned_limit - assigned;
		if (needed <= 0)
			return;
	}

	dev_dbg(xpc_chan, "create %d new kthreads, partid=%d, channel=%d\n",
		needed, ch->partid, ch->number);

	xpc_create_kthreads(ch, needed, 0);
}