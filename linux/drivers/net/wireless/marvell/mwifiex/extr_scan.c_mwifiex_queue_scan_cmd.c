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
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int /*<<< orphan*/  scan_pending_q_lock; int /*<<< orphan*/  scan_pending_q; int /*<<< orphan*/  scan_wait_q_woken; } ;
struct cmd_ctrl_node {int wait_q_enabled; int /*<<< orphan*/  list; int /*<<< orphan*/ * condition; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void
mwifiex_queue_scan_cmd(struct mwifiex_private *priv,
		       struct cmd_ctrl_node *cmd_node)
{
	struct mwifiex_adapter *adapter = priv->adapter;

	cmd_node->wait_q_enabled = true;
	cmd_node->condition = &adapter->scan_wait_q_woken;
	spin_lock_bh(&adapter->scan_pending_q_lock);
	list_add_tail(&cmd_node->list, &adapter->scan_pending_q);
	spin_unlock_bh(&adapter->scan_pending_q_lock);
}