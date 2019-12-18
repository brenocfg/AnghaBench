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
struct mwifiex_adapter {int /*<<< orphan*/  mwifiex_cmd_lock; struct cmd_ctrl_node* curr_cmd; } ;
struct cmd_ctrl_node {scalar_t__ wait_q_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_cancel_scan (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_recycle_cmd_node (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwifiex_cancel_pending_ioctl(struct mwifiex_adapter *adapter)
{
	struct cmd_ctrl_node *cmd_node = NULL;

	if ((adapter->curr_cmd) &&
	    (adapter->curr_cmd->wait_q_enabled)) {
		spin_lock_bh(&adapter->mwifiex_cmd_lock);
		cmd_node = adapter->curr_cmd;
		/* setting curr_cmd to NULL is quite dangerous, because
		 * mwifiex_process_cmdresp checks curr_cmd to be != NULL
		 * at the beginning then relies on it and dereferences
		 * it at will
		 * this probably works since mwifiex_cmd_timeout_func
		 * is the only caller of this function and responses
		 * at that point
		 */
		adapter->curr_cmd = NULL;
		spin_unlock_bh(&adapter->mwifiex_cmd_lock);

		mwifiex_recycle_cmd_node(adapter, cmd_node);
	}

	mwifiex_cancel_scan(adapter);
}