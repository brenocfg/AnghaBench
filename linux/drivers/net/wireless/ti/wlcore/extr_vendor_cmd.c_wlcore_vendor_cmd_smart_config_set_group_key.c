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
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct nlattr {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX_WLCORE_VENDOR_ATTR ; 
 int NUM_WLCORE_VENDOR_ATTR ; 
 scalar_t__ WLCORE_STATE_ON ; 
 size_t WLCORE_VENDOR_ATTR_GROUP_ID ; 
 size_t WLCORE_VENDOR_ATTR_GROUP_KEY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 int nla_parse_deprecated (struct nlattr**,int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int wlcore_smart_config_set_group_key (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_vendor_attr_policy ; 

__attribute__((used)) static int
wlcore_vendor_cmd_smart_config_set_group_key(struct wiphy *wiphy,
					     struct wireless_dev *wdev,
					     const void *data, int data_len)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct wl1271 *wl = hw->priv;
	struct nlattr *tb[NUM_WLCORE_VENDOR_ATTR];
	int ret;

	wl1271_debug(DEBUG_CMD, "testmode cmd smart config set group key");

	if (!data)
		return -EINVAL;

	ret = nla_parse_deprecated(tb, MAX_WLCORE_VENDOR_ATTR, data, data_len,
				   wlcore_vendor_attr_policy, NULL);
	if (ret)
		return ret;

	if (!tb[WLCORE_VENDOR_ATTR_GROUP_ID] ||
	    !tb[WLCORE_VENDOR_ATTR_GROUP_KEY])
		return -EINVAL;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON)) {
		ret = -EINVAL;
		goto out;
	}

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	ret = wlcore_smart_config_set_group_key(wl,
			nla_get_u32(tb[WLCORE_VENDOR_ATTR_GROUP_ID]),
			nla_len(tb[WLCORE_VENDOR_ATTR_GROUP_KEY]),
			nla_data(tb[WLCORE_VENDOR_ATTR_GROUP_KEY]));

	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	return ret;
}