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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {void* length; void* code; } ;
struct mwl8k_cmd_bbp_reg_access {int /*<<< orphan*/  value; TYPE_1__ header; void* offset; void* action; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_BBP_REG_ACCESS ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_bbp_reg_access*) ; 
 struct mwl8k_cmd_bbp_reg_access* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 

__attribute__((used)) static int
mwl8k_cmd_bbp_reg_access(struct ieee80211_hw *hw,
			 u16 action,
			 u16 offset,
			 u8 *value)
{
	struct mwl8k_cmd_bbp_reg_access *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_BBP_REG_ACCESS);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le16(action);
	cmd->offset = cpu_to_le16(offset);

	rc = mwl8k_post_cmd(hw, &cmd->header);

	if (!rc)
		*value = cmd->value;
	else
		*value = 0;

	kfree(cmd);

	return rc;
}