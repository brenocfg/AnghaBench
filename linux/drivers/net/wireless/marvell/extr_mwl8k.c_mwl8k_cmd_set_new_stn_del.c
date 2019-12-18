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
struct mwl8k_priv {int /*<<< orphan*/  stream_lock; struct mwl8k_ampdu_stream* ampdu; } ;
struct TYPE_4__ {void* length; void* code; } ;
struct mwl8k_cmd_set_new_stn {TYPE_2__ header; void* action; int /*<<< orphan*/  mac_addr; } ;
struct mwl8k_ampdu_stream {scalar_t__ state; int /*<<< orphan*/  idx; TYPE_1__* sta; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ AMPDU_NO_STREAM ; 
 scalar_t__ AMPDU_STREAM_ACTIVE ; 
 scalar_t__ AMPDU_STREAM_NEW ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET_NEW_STN ; 
 int MWL8K_NUM_AMPDU_STREAMS ; 
 int MWL8K_STA_ACTION_REMOVE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_new_stn*) ; 
 struct mwl8k_cmd_set_new_stn* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_destroy_ba (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int mwl8k_post_pervif_cmd (struct ieee80211_hw*,struct ieee80211_vif*,TYPE_2__*) ; 
 int /*<<< orphan*/  mwl8k_remove_stream (struct ieee80211_hw*,struct mwl8k_ampdu_stream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwl8k_cmd_set_new_stn_del(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif, u8 *addr)
{
	struct mwl8k_cmd_set_new_stn *cmd;
	struct mwl8k_priv *priv = hw->priv;
	int rc, i;
	u8 idx;

	spin_lock(&priv->stream_lock);
	/* Destroy any active ampdu streams for this sta */
	for (i = 0; i < MWL8K_NUM_AMPDU_STREAMS; i++) {
		struct mwl8k_ampdu_stream *s;
		s = &priv->ampdu[i];
		if (s->state != AMPDU_NO_STREAM) {
			if (memcmp(s->sta->addr, addr, ETH_ALEN) == 0) {
				if (s->state == AMPDU_STREAM_ACTIVE) {
					idx = s->idx;
					spin_unlock(&priv->stream_lock);
					mwl8k_destroy_ba(hw, idx);
					spin_lock(&priv->stream_lock);
				} else if (s->state == AMPDU_STREAM_NEW) {
					mwl8k_remove_stream(hw, s);
				}
			}
		}
	}

	spin_unlock(&priv->stream_lock);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_NEW_STN);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	memcpy(cmd->mac_addr, addr, ETH_ALEN);
	cmd->action = cpu_to_le16(MWL8K_STA_ACTION_REMOVE);

	rc = mwl8k_post_pervif_cmd(hw, vif, &cmd->header);
	kfree(cmd);

	return rc;
}