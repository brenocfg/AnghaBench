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
struct TYPE_4__ {void* length; void* code; } ;
struct mwl8k_cmd_finalize_join {TYPE_2__ header; int /*<<< orphan*/  beacon_data; int /*<<< orphan*/  sleep_interval; } ;
struct TYPE_3__ {int /*<<< orphan*/  beacon; } ;
struct ieee80211_mgmt {TYPE_1__ u; int /*<<< orphan*/  frame_control; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET_FINALIZE_JOIN ; 
 int MWL8K_FJ_BEACON_MAXLEN ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_finalize_join*) ; 
 struct mwl8k_cmd_finalize_join* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_2__*) ; 

__attribute__((used)) static int mwl8k_cmd_finalize_join(struct ieee80211_hw *hw, void *frame,
				   int framelen, int dtim)
{
	struct mwl8k_cmd_finalize_join *cmd;
	struct ieee80211_mgmt *payload = frame;
	int payload_len;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_FINALIZE_JOIN);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->sleep_interval = cpu_to_le32(dtim ? dtim : 1);

	payload_len = framelen - ieee80211_hdrlen(payload->frame_control);
	if (payload_len < 0)
		payload_len = 0;
	else if (payload_len > MWL8K_FJ_BEACON_MAXLEN)
		payload_len = MWL8K_FJ_BEACON_MAXLEN;

	memcpy(cmd->beacon_data, &payload->u.beacon, payload_len);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}