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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct wil_sta_info {int dummy; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum wmi_key_usage { ____Placeholder_wmi_key_usage } wmi_key_usage ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct wil_sta_info*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct wil_sta_info*) ; 
 int /*<<< orphan*/ * key_usage_str ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 struct wireless_dev* vif_to_wdev (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_del_rx_key (int /*<<< orphan*/ ,int,struct wil_sta_info*) ; 
 int wil_detect_key_usage (struct wireless_dev*,int) ; 
 struct wil_sta_info* wil_find_sta_by_key_usage (struct wil6210_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_del_cipher_key (struct wil6210_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int wil_cfg80211_del_key(struct wiphy *wiphy,
				struct net_device *ndev,
				u8 key_index, bool pairwise,
				const u8 *mac_addr)
{
	struct wil6210_vif *vif = ndev_to_vif(ndev);
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wireless_dev *wdev = vif_to_wdev(vif);
	enum wmi_key_usage key_usage = wil_detect_key_usage(wdev, pairwise);
	struct wil_sta_info *cs = wil_find_sta_by_key_usage(wil, vif->mid,
							    key_usage,
							    mac_addr);

	wil_dbg_misc(wil, "del_key: %pM %s[%d]\n", mac_addr,
		     key_usage_str[key_usage], key_index);

	if (IS_ERR(cs))
		wil_info(wil, "Not connected, %pM %s[%d]\n",
			 mac_addr, key_usage_str[key_usage], key_index);

	if (!IS_ERR_OR_NULL(cs))
		wil_del_rx_key(key_index, key_usage, cs);

	return wmi_del_cipher_key(vif, key_index, mac_addr, key_usage);
}