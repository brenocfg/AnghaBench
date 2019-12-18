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
typedef  int u32 ;
struct wl18xx_cmd_channel_switch {int /*<<< orphan*/  channel_type; int /*<<< orphan*/  local_supported_rates; int /*<<< orphan*/  band; int /*<<< orphan*/  stop_tx; int /*<<< orphan*/  switch_time; int /*<<< orphan*/  channel; int /*<<< orphan*/  role_id; } ;
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  channel_type; scalar_t__ p2p; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_channel_switch {TYPE_2__ chandef; int /*<<< orphan*/  block_tx; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int band; int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  CMD_CHANNEL_SWITCH ; 
 int CONF_TX_CCK_RATES ; 
 int CONF_TX_ENABLED_RATES ; 
 int CONF_TX_MCS_RATES ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NL80211_BAND_2GHZ 129 
#define  NL80211_BAND_5GHZ 128 
 int /*<<< orphan*/  WLCORE_BAND_2_4GHZ ; 
 int /*<<< orphan*/  WLCORE_BAND_5GHZ ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct wl18xx_cmd_channel_switch*) ; 
 struct wl18xx_cmd_channel_switch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_cmd_channel_switch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 
 int wlcore_hw_ap_get_mimo_wide_rate_mask (struct wl1271*,struct wl12xx_vif*) ; 
 int wlcore_hw_sta_get_ap_rate_mask (struct wl1271*,struct wl12xx_vif*) ; 

int wl18xx_cmd_channel_switch(struct wl1271 *wl,
			      struct wl12xx_vif *wlvif,
			      struct ieee80211_channel_switch *ch_switch)
{
	struct wl18xx_cmd_channel_switch *cmd;
	u32 supported_rates;
	int ret;

	wl1271_debug(DEBUG_ACX, "cmd channel switch (count=%d)",
		     ch_switch->count);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->role_id = wlvif->role_id;
	cmd->channel = ch_switch->chandef.chan->hw_value;
	cmd->switch_time = ch_switch->count;
	cmd->stop_tx = ch_switch->block_tx;

	switch (ch_switch->chandef.chan->band) {
	case NL80211_BAND_2GHZ:
		cmd->band = WLCORE_BAND_2_4GHZ;
		break;
	case NL80211_BAND_5GHZ:
		cmd->band = WLCORE_BAND_5GHZ;
		break;
	default:
		wl1271_error("invalid channel switch band: %d",
			     ch_switch->chandef.chan->band);
		ret = -EINVAL;
		goto out_free;
	}

	supported_rates = CONF_TX_ENABLED_RATES | CONF_TX_MCS_RATES;
	if (wlvif->bss_type == BSS_TYPE_STA_BSS)
		supported_rates |= wlcore_hw_sta_get_ap_rate_mask(wl, wlvif);
	else
		supported_rates |=
			wlcore_hw_ap_get_mimo_wide_rate_mask(wl, wlvif);
	if (wlvif->p2p)
		supported_rates &= ~CONF_TX_CCK_RATES;
	cmd->local_supported_rates = cpu_to_le32(supported_rates);
	cmd->channel_type = wlvif->channel_type;

	ret = wl1271_cmd_send(wl, CMD_CHANNEL_SWITCH, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send channel switch command");
		goto out_free;
	}

out_free:
	kfree(cmd);
out:
	return ret;
}