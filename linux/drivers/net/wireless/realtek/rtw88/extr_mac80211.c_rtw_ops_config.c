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
typedef  int u32 ;
struct rtw_dev {int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int flags; } ;
struct ieee80211_hw {TYPE_1__ conf; struct rtw_dev* priv; } ;

/* Variables and functions */
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_IDLE ; 
 int IEEE80211_CONF_IDLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_enter_ips (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int rtw_leave_ips (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_set_channel (struct rtw_dev*) ; 

__attribute__((used)) static int rtw_ops_config(struct ieee80211_hw *hw, u32 changed)
{
	struct rtw_dev *rtwdev = hw->priv;
	int ret = 0;

	mutex_lock(&rtwdev->mutex);

	if (changed & IEEE80211_CONF_CHANGE_IDLE) {
		if (hw->conf.flags & IEEE80211_CONF_IDLE) {
			rtw_enter_ips(rtwdev);
		} else {
			ret = rtw_leave_ips(rtwdev);
			if (ret) {
				rtw_err(rtwdev, "failed to leave idle state\n");
				goto out;
			}
		}
	}

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL)
		rtw_set_channel(rtwdev);

out:
	mutex_unlock(&rtwdev->mutex);
	return ret;
}