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
struct rsi_hw {struct rsi_common* priv; } ;
struct rsi_common {int mac_ops_resumed; scalar_t__ fsm_state; int wow_flags; int bgscan_en; int /*<<< orphan*/  mutex; struct cfg80211_scan_request* hwscan; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {struct ieee80211_bss_conf bss_conf; } ;
struct cfg80211_scan_request {scalar_t__ n_channels; } ;
struct ieee80211_scan_request {struct cfg80211_scan_request req; } ;
struct ieee80211_hw {struct rsi_hw* priv; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ FSM_MAC_INIT_DONE ; 
 int /*<<< orphan*/  INFO_ZONE ; 
 int /*<<< orphan*/  RSI_START_BGSCAN ; 
 int RSI_WOW_ENABLED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_send_bgscan_params (struct rsi_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_send_bgscan_probe_req (struct rsi_common*,struct ieee80211_vif*) ; 

__attribute__((used)) static int rsi_mac80211_hw_scan_start(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_scan_request *hw_req)
{
	struct cfg80211_scan_request *scan_req = &hw_req->req;
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;
	struct ieee80211_bss_conf *bss = &vif->bss_conf;

	rsi_dbg(INFO_ZONE, "***** Hardware scan start *****\n");
	common->mac_ops_resumed = false;

	if (common->fsm_state != FSM_MAC_INIT_DONE)
		return -ENODEV;

	if ((common->wow_flags & RSI_WOW_ENABLED) ||
	    scan_req->n_channels == 0)
		return -EINVAL;

	/* Scan already in progress. So return */
	if (common->bgscan_en)
		return -EBUSY;

	/* If STA is not connected, return with special value 1, in order
	 * to start sw_scan in mac80211
	 */
	if (!bss->assoc)
		return 1;

	mutex_lock(&common->mutex);
	common->hwscan = scan_req;
	if (!rsi_send_bgscan_params(common, RSI_START_BGSCAN)) {
		if (!rsi_send_bgscan_probe_req(common, vif)) {
			rsi_dbg(INFO_ZONE, "Background scan started...\n");
			common->bgscan_en = true;
		}
	}
	mutex_unlock(&common->mutex);

	return 0;
}