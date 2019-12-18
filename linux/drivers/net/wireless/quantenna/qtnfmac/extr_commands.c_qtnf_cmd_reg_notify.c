#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct sk_buff {scalar_t__ data; } ;
struct regulatory_request {int initiator; int user_reg_hint_type; int dfs_region; int /*<<< orphan*/ * alpha2; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; struct qtnf_bus* bus; } ;
struct qtnf_bus {int dummy; } ;
struct qlink_cmd_reg_notify {int slave_radar; scalar_t__ num_channels; int /*<<< orphan*/  dfs_region; int /*<<< orphan*/  user_reg_hint_type; int /*<<< orphan*/  initiator; int /*<<< orphan*/ * alpha2; } ;
struct ieee80211_supported_band {unsigned int n_channels; int /*<<< orphan*/ * channels; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int ENOMEM ; 
#define  NL80211_DFS_ETSI 137 
#define  NL80211_DFS_FCC 136 
#define  NL80211_DFS_JP 135 
#define  NL80211_REGDOM_SET_BY_CORE 134 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 133 
#define  NL80211_REGDOM_SET_BY_DRIVER 132 
#define  NL80211_REGDOM_SET_BY_USER 131 
#define  NL80211_USER_REG_HINT_CELL_BASE 130 
#define  NL80211_USER_REG_HINT_INDOOR 129 
#define  NL80211_USER_REG_HINT_USER 128 
 int NUM_NL80211_BANDS ; 
 int /*<<< orphan*/  QLINK_CMD_REG_NOTIFY ; 
 int /*<<< orphan*/  QLINK_DFS_ETSI ; 
 int /*<<< orphan*/  QLINK_DFS_FCC ; 
 int /*<<< orphan*/  QLINK_DFS_JP ; 
 int /*<<< orphan*/  QLINK_DFS_UNSET ; 
 int /*<<< orphan*/  QLINK_REGDOM_SET_BY_CORE ; 
 int /*<<< orphan*/  QLINK_REGDOM_SET_BY_COUNTRY_IE ; 
 int /*<<< orphan*/  QLINK_REGDOM_SET_BY_DRIVER ; 
 int /*<<< orphan*/  QLINK_REGDOM_SET_BY_USER ; 
 int /*<<< orphan*/  QLINK_USER_REG_HINT_CELL_BASE ; 
 int /*<<< orphan*/  QLINK_USER_REG_HINT_INDOOR ; 
 int /*<<< orphan*/  QLINK_USER_REG_HINT_USER ; 
 int /*<<< orphan*/  QLINK_VIFID_RSVD ; 
 struct wiphy* priv_to_wiphy (struct qtnf_wmac*) ; 
 int /*<<< orphan*/  qtnf_bus_lock (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (struct qtnf_bus*) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qtnf_cmd_channel_tlv_add (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int qtnf_cmd_send (struct qtnf_bus*,struct sk_buff*) ; 

int qtnf_cmd_reg_notify(struct qtnf_wmac *mac, struct regulatory_request *req,
			bool slave_radar)
{
	struct wiphy *wiphy = priv_to_wiphy(mac);
	struct qtnf_bus *bus = mac->bus;
	struct sk_buff *cmd_skb;
	int ret;
	struct qlink_cmd_reg_notify *cmd;
	enum nl80211_band band;
	const struct ieee80211_supported_band *cfg_band;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, QLINK_VIFID_RSVD,
					    QLINK_CMD_REG_NOTIFY,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	cmd = (struct qlink_cmd_reg_notify *)cmd_skb->data;
	cmd->alpha2[0] = req->alpha2[0];
	cmd->alpha2[1] = req->alpha2[1];

	switch (req->initiator) {
	case NL80211_REGDOM_SET_BY_CORE:
		cmd->initiator = QLINK_REGDOM_SET_BY_CORE;
		break;
	case NL80211_REGDOM_SET_BY_USER:
		cmd->initiator = QLINK_REGDOM_SET_BY_USER;
		break;
	case NL80211_REGDOM_SET_BY_DRIVER:
		cmd->initiator = QLINK_REGDOM_SET_BY_DRIVER;
		break;
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		cmd->initiator = QLINK_REGDOM_SET_BY_COUNTRY_IE;
		break;
	}

	switch (req->user_reg_hint_type) {
	case NL80211_USER_REG_HINT_USER:
		cmd->user_reg_hint_type = QLINK_USER_REG_HINT_USER;
		break;
	case NL80211_USER_REG_HINT_CELL_BASE:
		cmd->user_reg_hint_type = QLINK_USER_REG_HINT_CELL_BASE;
		break;
	case NL80211_USER_REG_HINT_INDOOR:
		cmd->user_reg_hint_type = QLINK_USER_REG_HINT_INDOOR;
		break;
	}

	switch (req->dfs_region) {
	case NL80211_DFS_FCC:
		cmd->dfs_region = QLINK_DFS_FCC;
		break;
	case NL80211_DFS_ETSI:
		cmd->dfs_region = QLINK_DFS_ETSI;
		break;
	case NL80211_DFS_JP:
		cmd->dfs_region = QLINK_DFS_JP;
		break;
	default:
		cmd->dfs_region = QLINK_DFS_UNSET;
		break;
	}

	cmd->slave_radar = slave_radar;
	cmd->num_channels = 0;

	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		unsigned int i;

		cfg_band = wiphy->bands[band];
		if (!cfg_band)
			continue;

		cmd->num_channels += cfg_band->n_channels;

		for (i = 0; i < cfg_band->n_channels; ++i) {
			qtnf_cmd_channel_tlv_add(cmd_skb,
						 &cfg_band->channels[i]);
		}
	}

	qtnf_bus_lock(bus);
	ret = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unlock(bus);

	return ret;
}