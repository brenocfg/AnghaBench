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
struct mwifiex_adapter {int /*<<< orphan*/  cmd_pending; } ;
struct host_cmd_ds_command {int /*<<< orphan*/  command; } ;
struct cmd_ctrl_node {TYPE_1__* cmd_skb; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_insert_cmd_to_free_q (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 

void mwifiex_recycle_cmd_node(struct mwifiex_adapter *adapter,
			      struct cmd_ctrl_node *cmd_node)
{
	struct host_cmd_ds_command *host_cmd = (void *)cmd_node->cmd_skb->data;

	mwifiex_insert_cmd_to_free_q(adapter, cmd_node);

	atomic_dec(&adapter->cmd_pending);
	mwifiex_dbg(adapter, CMD,
		    "cmd: FREE_CMD: cmd=%#x, cmd_pending=%d\n",
		le16_to_cpu(host_cmd->command),
		atomic_read(&adapter->cmd_pending));
}