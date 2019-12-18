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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl1251 {scalar_t__* bssid; int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  rx_config; } ;
struct cmd_join {int basic_rate_set; int /*<<< orphan*/  ctrl; scalar_t__ channel; scalar_t__ bss_type; scalar_t__ dtim_interval; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  rx_filter_options; int /*<<< orphan*/  rx_config_options; int /*<<< orphan*/  bssid_lsb; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  CMD_START_JOIN ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  JOIN_CMD_CTRL_TX_FLUSH ; 
 int RATE_MASK_11MBPS ; 
 int RATE_MASK_1MBPS ; 
 int RATE_MASK_2MBPS ; 
 int RATE_MASK_5_5MBPS ; 
 int /*<<< orphan*/  kfree (struct cmd_join*) ; 
 struct cmd_join* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_send (struct wl1251*,int /*<<< orphan*/ ,struct cmd_join*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 

int wl1251_cmd_join(struct wl1251 *wl, u8 bss_type, u8 channel,
		    u16 beacon_interval, u8 dtim_interval)
{
	struct cmd_join *join;
	int ret, i;
	u8 *bssid;

	join = kzalloc(sizeof(*join), GFP_KERNEL);
	if (!join) {
		ret = -ENOMEM;
		goto out;
	}

	wl1251_debug(DEBUG_CMD, "cmd join%s ch %d %d/%d",
		     bss_type == BSS_TYPE_IBSS ? " ibss" : "",
		     channel, beacon_interval, dtim_interval);

	/* Reverse order BSSID */
	bssid = (u8 *) &join->bssid_lsb;
	for (i = 0; i < ETH_ALEN; i++)
		bssid[i] = wl->bssid[ETH_ALEN - i - 1];

	join->rx_config_options = wl->rx_config;
	join->rx_filter_options = wl->rx_filter;

	join->basic_rate_set = RATE_MASK_1MBPS | RATE_MASK_2MBPS |
		RATE_MASK_5_5MBPS | RATE_MASK_11MBPS;

	join->beacon_interval = beacon_interval;
	join->dtim_interval = dtim_interval;
	join->bss_type = bss_type;
	join->channel = channel;
	join->ctrl = JOIN_CMD_CTRL_TX_FLUSH;

	ret = wl1251_cmd_send(wl, CMD_START_JOIN, join, sizeof(*join));
	if (ret < 0) {
		wl1251_error("failed to initiate cmd join");
		goto out;
	}

out:
	kfree(join);
	return ret;
}