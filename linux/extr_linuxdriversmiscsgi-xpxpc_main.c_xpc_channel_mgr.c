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
struct TYPE_2__ {scalar_t__ all_flags; } ;
struct xpc_partition {scalar_t__ act_state; int /*<<< orphan*/  channel_mgr_requests; int /*<<< orphan*/  nchannels_active; TYPE_1__ chctl; int /*<<< orphan*/  channel_mgr_wq; } ;

/* Variables and functions */
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpc_partition_disengaged (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_process_sent_chctl_flags (struct xpc_partition*) ; 

__attribute__((used)) static void
xpc_channel_mgr(struct xpc_partition *part)
{
	while (part->act_state != XPC_P_AS_DEACTIVATING ||
	       atomic_read(&part->nchannels_active) > 0 ||
	       !xpc_partition_disengaged(part)) {

		xpc_process_sent_chctl_flags(part);

		/*
		 * Wait until we've been requested to activate kthreads or
		 * all of the channel's message queues have been torn down or
		 * a signal is pending.
		 *
		 * The channel_mgr_requests is set to 1 after being awakened,
		 * This is done to prevent the channel mgr from making one pass
		 * through the loop for each request, since he will
		 * be servicing all the requests in one pass. The reason it's
		 * set to 1 instead of 0 is so that other kthreads will know
		 * that the channel mgr is running and won't bother trying to
		 * wake him up.
		 */
		atomic_dec(&part->channel_mgr_requests);
		(void)wait_event_interruptible(part->channel_mgr_wq,
				(atomic_read(&part->channel_mgr_requests) > 0 ||
				 part->chctl.all_flags != 0 ||
				 (part->act_state == XPC_P_AS_DEACTIVATING &&
				 atomic_read(&part->nchannels_active) == 0 &&
				 xpc_partition_disengaged(part))));
		atomic_set(&part->channel_mgr_requests, 1);
	}
}