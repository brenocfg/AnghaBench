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
struct mwl8k_priv {scalar_t__ channel_time; struct ieee80211_channel* acs_chan; scalar_t__ sw_scan_start; } ;
struct TYPE_3__ {void* length; void* code; } ;
struct mwl8k_cmd_set_rf_channel {TYPE_1__ header; int /*<<< orphan*/  channel_flags; int /*<<< orphan*/  current_channel; void* action; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
struct TYPE_4__ {struct ieee80211_channel* chan; } ;
struct ieee80211_conf {TYPE_2__ chandef; } ;
struct ieee80211_channel {scalar_t__ band; int /*<<< orphan*/  hw_value; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET ; 
 int MWL8K_CMD_SET_RF_CHANNEL ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int NL80211_CHAN_HT20 ; 
 int NL80211_CHAN_HT40MINUS ; 
 int NL80211_CHAN_HT40PLUS ; 
 int NL80211_CHAN_NO_HT ; 
 int cfg80211_get_chandef_type (TYPE_2__*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_rf_channel*) ; 
 struct mwl8k_cmd_set_rf_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 
 int /*<<< orphan*/  mwl8k_update_survey (struct mwl8k_priv*,struct ieee80211_channel*) ; 

__attribute__((used)) static int mwl8k_cmd_set_rf_channel(struct ieee80211_hw *hw,
				    struct ieee80211_conf *conf)
{
	struct ieee80211_channel *channel = conf->chandef.chan;
	enum nl80211_channel_type channel_type =
		cfg80211_get_chandef_type(&conf->chandef);
	struct mwl8k_cmd_set_rf_channel *cmd;
	struct mwl8k_priv *priv = hw->priv;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_RF_CHANNEL);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->current_channel = channel->hw_value;

	if (channel->band == NL80211_BAND_2GHZ)
		cmd->channel_flags |= cpu_to_le32(0x00000001);
	else if (channel->band == NL80211_BAND_5GHZ)
		cmd->channel_flags |= cpu_to_le32(0x00000004);

	if (!priv->sw_scan_start) {
		if (channel_type == NL80211_CHAN_NO_HT ||
		    channel_type == NL80211_CHAN_HT20)
			cmd->channel_flags |= cpu_to_le32(0x00000080);
		else if (channel_type == NL80211_CHAN_HT40MINUS)
			cmd->channel_flags |= cpu_to_le32(0x000001900);
		else if (channel_type == NL80211_CHAN_HT40PLUS)
			cmd->channel_flags |= cpu_to_le32(0x000000900);
	} else {
		cmd->channel_flags |= cpu_to_le32(0x00000080);
	}

	if (priv->sw_scan_start) {
		/* Store current channel stats
		 * before switching to newer one.
		 * This will be processed only for AP fw.
		 */
		if (priv->channel_time != 0)
			mwl8k_update_survey(priv, priv->acs_chan);

		priv->channel_time = jiffies;
		priv->acs_chan =  channel;
	}

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}