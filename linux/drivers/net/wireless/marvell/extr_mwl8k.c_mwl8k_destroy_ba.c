#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {void* length; void* code; } ;
struct TYPE_3__ {void* ba_context; } ;
struct mwl8k_cmd_bastream {TYPE_2__ header; TYPE_1__ destroy_params; void* action; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MWL8K_BA_DESTROY ; 
 int MWL8K_CMD_BASTREAM ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_bastream*) ; 
 struct mwl8k_cmd_bastream* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_post_cmd (struct ieee80211_hw*,TYPE_2__*) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwl8k_destroy_ba(struct ieee80211_hw *hw,
			     u8 idx)
{
	struct mwl8k_cmd_bastream *cmd;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_BASTREAM);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le32(MWL8K_BA_DESTROY);

	cmd->destroy_params.ba_context = cpu_to_le32(idx);
	mwl8k_post_cmd(hw, &cmd->header);

	wiphy_debug(hw->wiphy, "Deleted BA stream index %d\n", idx);

	kfree(cmd);
}