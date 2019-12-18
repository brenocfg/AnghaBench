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
struct wiphy {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; scalar_t__ current_bss; } ;
struct mwifiex_private {int scan_block; scalar_t__ bss_type; int /*<<< orphan*/  cfg_bssid; int /*<<< orphan*/  netdev; struct mwifiex_adapter* adapter; int /*<<< orphan*/  bss_mode; TYPE_1__ wdev; } ;
struct mwifiex_adapter {scalar_t__ auto_tdls; int /*<<< orphan*/  fw_cap_info; int /*<<< orphan*/  work_flags; } ;
struct cfg80211_connect_params {int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; scalar_t__ ssid; scalar_t__ ssid_len; } ;

/* Variables and functions */
 int EALREADY ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GET_BSS_ROLE (struct mwifiex_private*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ ISSUPP_TDLS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG ; 
 scalar_t__ MWIFIEX_BSS_ROLE_STA ; 
 scalar_t__ MWIFIEX_BSS_TYPE_STA ; 
 int /*<<< orphan*/  MWIFIEX_IS_CMD_TIMEDOUT ; 
 int /*<<< orphan*/  MWIFIEX_SURPRISE_REMOVED ; 
 int WLAN_STATUS_SUCCESS ; 
 int WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  cfg80211_connect_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_sched_scan_stopped_rtnl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int mwifiex_cfg80211_assoc (struct mwifiex_private*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_connect_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int,...) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  mwifiex_setup_auto_tdls_timer (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_stop_bg_scan (struct mwifiex_private*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwifiex_cfg80211_connect(struct wiphy *wiphy, struct net_device *dev,
			 struct cfg80211_connect_params *sme)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);
	struct mwifiex_adapter *adapter = priv->adapter;
	int ret;

	if (GET_BSS_ROLE(priv) != MWIFIEX_BSS_ROLE_STA) {
		mwifiex_dbg(adapter, ERROR,
			    "%s: reject infra assoc request in non-STA role\n",
			    dev->name);
		return -EINVAL;
	}

	if (priv->wdev.current_bss) {
		mwifiex_dbg(adapter, ERROR,
			    "%s: already connected\n", dev->name);
		return -EALREADY;
	}

	if (priv->scan_block)
		priv->scan_block = false;

	if (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags) ||
	    test_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags)) {
		mwifiex_dbg(adapter, ERROR,
			    "%s: Ignore connection.\t"
			    "Card removed or FW in bad state\n",
			    dev->name);
		return -EFAULT;
	}

	mwifiex_dbg(adapter, INFO,
		    "info: Trying to associate to %.*s and bssid %pM\n",
		    (int)sme->ssid_len, (char *)sme->ssid, sme->bssid);

	if (!mwifiex_stop_bg_scan(priv))
		cfg80211_sched_scan_stopped_rtnl(priv->wdev.wiphy, 0);

	ret = mwifiex_cfg80211_assoc(priv, sme->ssid_len, sme->ssid, sme->bssid,
				     priv->bss_mode, sme->channel, sme, 0);
	if (!ret) {
		cfg80211_connect_result(priv->netdev, priv->cfg_bssid, NULL, 0,
					NULL, 0, WLAN_STATUS_SUCCESS,
					GFP_KERNEL);
		mwifiex_dbg(priv->adapter, MSG,
			    "info: associated to bssid %pM successfully\n",
			    priv->cfg_bssid);
		if (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
		    priv->adapter->auto_tdls &&
		    priv->bss_type == MWIFIEX_BSS_TYPE_STA)
			mwifiex_setup_auto_tdls_timer(priv);
	} else {
		mwifiex_dbg(priv->adapter, ERROR,
			    "info: association to bssid %pM failed\n",
			    priv->cfg_bssid);
		eth_zero_addr(priv->cfg_bssid);

		if (ret > 0)
			cfg80211_connect_result(priv->netdev, priv->cfg_bssid,
						NULL, 0, NULL, 0, ret,
						GFP_KERNEL);
		else
			cfg80211_connect_result(priv->netdev, priv->cfg_bssid,
						NULL, 0, NULL, 0,
						WLAN_STATUS_UNSPECIFIED_FAILURE,
						GFP_KERNEL);
	}

	return 0;
}