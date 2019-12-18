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
struct rtw_sta_info {int /*<<< orphan*/  mac_id; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sta_cnt; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_fw_media_status_report (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_info (struct rtw_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_release_macid (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw_ops_sta_remove(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      struct ieee80211_sta *sta)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_sta_info *si = (struct rtw_sta_info *)sta->drv_priv;

	mutex_lock(&rtwdev->mutex);

	rtw_release_macid(rtwdev, si->mac_id);
	rtw_fw_media_status_report(rtwdev, si->mac_id, false);

	rtwdev->sta_cnt--;

	rtw_info(rtwdev, "sta %pM with macid %d left\n",
		 sta->addr, si->mac_id);

	mutex_unlock(&rtwdev->mutex);
	return 0;
}