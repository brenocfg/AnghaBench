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
struct TYPE_2__ {int /*<<< orphan*/  (* cmdrsp_complete ) (struct mwifiex_adapter*,int /*<<< orphan*/ *) ;} ;
struct mwifiex_adapter {TYPE_1__ if_ops; } ;
struct cmd_ctrl_node {int wait_q_enabled; int /*<<< orphan*/ * resp_skb; scalar_t__ cmd_skb; int /*<<< orphan*/ * data_buf; scalar_t__ cmd_flag; scalar_t__ cmd_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_trim (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwifiex_clean_cmd_node(struct mwifiex_adapter *adapter,
		       struct cmd_ctrl_node *cmd_node)
{
	cmd_node->cmd_no = 0;
	cmd_node->cmd_flag = 0;
	cmd_node->data_buf = NULL;
	cmd_node->wait_q_enabled = false;

	if (cmd_node->cmd_skb)
		skb_trim(cmd_node->cmd_skb, 0);

	if (cmd_node->resp_skb) {
		adapter->if_ops.cmdrsp_complete(adapter, cmd_node->resp_skb);
		cmd_node->resp_skb = NULL;
	}
}