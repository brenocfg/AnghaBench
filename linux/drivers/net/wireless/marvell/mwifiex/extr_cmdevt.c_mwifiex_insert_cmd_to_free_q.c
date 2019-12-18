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
struct mwifiex_adapter {int /*<<< orphan*/  cmd_free_q_lock; int /*<<< orphan*/  cmd_free_q; } ;
struct cmd_ctrl_node {int /*<<< orphan*/  list; scalar_t__ wait_q_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_clean_cmd_node (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  mwifiex_complete_cmd (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwifiex_insert_cmd_to_free_q(struct mwifiex_adapter *adapter,
			     struct cmd_ctrl_node *cmd_node)
{
	if (!cmd_node)
		return;

	if (cmd_node->wait_q_enabled)
		mwifiex_complete_cmd(adapter, cmd_node);
	/* Clean the node */
	mwifiex_clean_cmd_node(adapter, cmd_node);

	/* Insert node into cmd_free_q */
	spin_lock_bh(&adapter->cmd_free_q_lock);
	list_add_tail(&cmd_node->list, &adapter->cmd_free_q);
	spin_unlock_bh(&adapter->cmd_free_q_lock);
}