#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int status; } ;
struct TYPE_5__ {unsigned int num_channels; unsigned int num_probe_requests; size_t ssid_len; int /*<<< orphan*/  ssid; scalar_t__ tid_trigger; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  scan_options; void* rx_filter_options; void* rx_config_options; } ;
struct wl1251_cmd_scan {TYPE_3__ header; TYPE_2__ params; TYPE_1__* channels; } ;
struct wl1251 {int /*<<< orphan*/  cmd_box_addr; int /*<<< orphan*/  bssid; } ;
struct ieee80211_channel {int /*<<< orphan*/  hw_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; scalar_t__ tx_power_att; scalar_t__ early_termination; int /*<<< orphan*/  bssid_msb; int /*<<< orphan*/  bssid_lsb; void* max_duration; void* min_duration; } ;

/* Variables and functions */
 int CFG_RX_ALL_GOOD ; 
 int CFG_RX_BCN_EN ; 
 int CFG_RX_MGMT_EN ; 
 int CFG_RX_PRSP_EN ; 
 int /*<<< orphan*/  CMD_SCAN ; 
 int CMD_STATUS_SUCCESS ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SCAN_MAX_NUM_OF_CHANNELS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WL1251_SCAN_MAX_DURATION ; 
 int WL1251_SCAN_MIN_DURATION ; 
 int WL1251_SCAN_OPT_PRIORITY_HIGH ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1251_cmd_scan*) ; 
 struct wl1251_cmd_scan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int wl1251_cmd_send (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_cmd_scan*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  wl1251_error (char*,int) ; 
 int /*<<< orphan*/  wl1251_mem_read (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_cmd_scan*,int) ; 

int wl1251_cmd_scan(struct wl1251 *wl, u8 *ssid, size_t ssid_len,
		    struct ieee80211_channel *channels[],
		    unsigned int n_channels, unsigned int n_probes)
{
	struct wl1251_cmd_scan *cmd;
	int i, ret = 0;

	wl1251_debug(DEBUG_CMD, "cmd scan channels %d", n_channels);

	WARN_ON(n_channels > SCAN_MAX_NUM_OF_CHANNELS);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->params.rx_config_options = cpu_to_le32(CFG_RX_ALL_GOOD);
	cmd->params.rx_filter_options = cpu_to_le32(CFG_RX_PRSP_EN |
						    CFG_RX_MGMT_EN |
						    CFG_RX_BCN_EN);
	cmd->params.scan_options = 0;
	/*
	 * Use high priority scan when not associated to prevent fw issue
	 * causing never-ending scans (sometimes 20+ minutes).
	 * Note: This bug may be caused by the fw's DTIM handling.
	 */
	if (is_zero_ether_addr(wl->bssid))
		cmd->params.scan_options |= cpu_to_le16(WL1251_SCAN_OPT_PRIORITY_HIGH);
	cmd->params.num_channels = n_channels;
	cmd->params.num_probe_requests = n_probes;
	cmd->params.tx_rate = cpu_to_le16(1 << 1); /* 2 Mbps */
	cmd->params.tid_trigger = 0;

	for (i = 0; i < n_channels; i++) {
		cmd->channels[i].min_duration =
			cpu_to_le32(WL1251_SCAN_MIN_DURATION);
		cmd->channels[i].max_duration =
			cpu_to_le32(WL1251_SCAN_MAX_DURATION);
		memset(&cmd->channels[i].bssid_lsb, 0xff, 4);
		memset(&cmd->channels[i].bssid_msb, 0xff, 2);
		cmd->channels[i].early_termination = 0;
		cmd->channels[i].tx_power_att = 0;
		cmd->channels[i].channel = channels[i]->hw_value;
	}

	cmd->params.ssid_len = ssid_len;
	if (ssid)
		memcpy(cmd->params.ssid, ssid, ssid_len);

	ret = wl1251_cmd_send(wl, CMD_SCAN, cmd, sizeof(*cmd));
	if (ret < 0) {
		wl1251_error("cmd scan failed: %d", ret);
		goto out;
	}

	wl1251_mem_read(wl, wl->cmd_box_addr, cmd, sizeof(*cmd));

	if (cmd->header.status != CMD_STATUS_SUCCESS) {
		wl1251_error("cmd scan status wasn't success: %d",
			     cmd->header.status);
		ret = -EIO;
		goto out;
	}

out:
	kfree(cmd);
	return ret;
}