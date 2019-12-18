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
struct TYPE_2__ {void* length; void* code; } ;
struct mwl8k_cmd_get_watchdog_bitmap {int /*<<< orphan*/  bitmap; TYPE_1__ header; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_GET_WATCHDOG_BITMAP ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_get_watchdog_bitmap*) ; 
 struct mwl8k_cmd_get_watchdog_bitmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 

__attribute__((used)) static int mwl8k_cmd_get_watchdog_bitmap(struct ieee80211_hw *hw, u8 *bitmap)
{
	struct mwl8k_cmd_get_watchdog_bitmap *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_GET_WATCHDOG_BITMAP);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));

	rc = mwl8k_post_cmd(hw, &cmd->header);
	if (!rc)
		*bitmap = cmd->bitmap;

	kfree(cmd);

	return rc;
}