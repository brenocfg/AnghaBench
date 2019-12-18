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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void* length; void* code; } ;
struct mwl8k_cmd_mimo_config {TYPE_1__ header; void* tx_antenna_map; void* rx_antenna_map; int /*<<< orphan*/  action; } ;
struct ieee80211_hw {int dummy; } ;
typedef  void* __u8 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_MIMO_CONFIG ; 
 scalar_t__ MWL8K_CMD_SET ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_mimo_config*) ; 
 struct mwl8k_cmd_mimo_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 

__attribute__((used)) static int mwl8k_cmd_mimo_config(struct ieee80211_hw *hw, __u8 rx, __u8 tx)
{
	struct mwl8k_cmd_mimo_config *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_MIMO_CONFIG);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le32((u32)MWL8K_CMD_SET);
	cmd->rx_antenna_map = rx;
	cmd->tx_antenna_map = tx;

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}