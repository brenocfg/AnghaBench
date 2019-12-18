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
struct TYPE_2__ {int status; int /*<<< orphan*/  wait; } ;
struct mwifiex_adapter {TYPE_1__ cmd_wait_q; } ;
struct cmd_ctrl_node {int /*<<< orphan*/ * condition; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  mwifiex_cancel_all_pending_cmd (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mwifiex_wait_queue_complete(struct mwifiex_adapter *adapter,
				struct cmd_ctrl_node *cmd_queued)
{
	int status;

	/* Wait for completion */
	status = wait_event_interruptible_timeout(adapter->cmd_wait_q.wait,
						  *(cmd_queued->condition),
						  (12 * HZ));
	if (status <= 0) {
		if (status == 0)
			status = -ETIMEDOUT;
		mwifiex_dbg(adapter, ERROR, "cmd_wait_q terminated: %d\n",
			    status);
		mwifiex_cancel_all_pending_cmd(adapter);
		return status;
	}

	status = adapter->cmd_wait_q.status;
	adapter->cmd_wait_q.status = 0;

	return status;
}