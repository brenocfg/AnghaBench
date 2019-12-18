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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* cmdrsp_complete ) (struct mwifiex_adapter*,scalar_t__) ;} ;
struct mwifiex_adapter {scalar_t__ iface_type; struct cmd_ctrl_node* cmd_pool; TYPE_1__ if_ops; } ;
struct cmd_ctrl_node {scalar_t__ resp_skb; scalar_t__ skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  FATAL ; 
 size_t MWIFIEX_NUM_OF_CMD_BUFFER ; 
 scalar_t__ MWIFIEX_USB ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*,scalar_t__) ; 

void mwifiex_free_cmd_buffer(struct mwifiex_adapter *adapter)
{
	struct cmd_ctrl_node *cmd_array;
	u32 i;

	/* Need to check if cmd pool is allocated or not */
	if (!adapter->cmd_pool) {
		mwifiex_dbg(adapter, FATAL,
			    "info: FREE_CMD_BUF: cmd_pool is null\n");
		return;
	}

	cmd_array = adapter->cmd_pool;

	/* Release shared memory buffers */
	for (i = 0; i < MWIFIEX_NUM_OF_CMD_BUFFER; i++) {
		if (cmd_array[i].skb) {
			mwifiex_dbg(adapter, CMD,
				    "cmd: free cmd buffer %d\n", i);
			dev_kfree_skb_any(cmd_array[i].skb);
		}
		if (!cmd_array[i].resp_skb)
			continue;

		if (adapter->iface_type == MWIFIEX_USB)
			adapter->if_ops.cmdrsp_complete(adapter,
							cmd_array[i].resp_skb);
		else
			dev_kfree_skb_any(cmd_array[i].resp_skb);
	}
	/* Release struct cmd_ctrl_node */
	if (adapter->cmd_pool) {
		mwifiex_dbg(adapter, CMD,
			    "cmd: free cmd pool\n");
		kfree(adapter->cmd_pool);
		adapter->cmd_pool = NULL;
	}
}