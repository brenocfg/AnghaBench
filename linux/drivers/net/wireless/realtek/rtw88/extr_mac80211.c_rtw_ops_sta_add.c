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
struct rtw_sta_info {scalar_t__ mac_id; int init_ra_lv; int /*<<< orphan*/  avg_rssi; struct ieee80211_vif* vif; struct ieee80211_sta* sta; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sta_cnt; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ RTW_MAX_MAC_ID_NUM ; 
 int /*<<< orphan*/  ewma_rssi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_acquire_macid (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_fw_media_status_report (struct rtw_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_info (struct rtw_dev*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtw_update_sta_info (struct rtw_dev*,struct rtw_sta_info*) ; 

__attribute__((used)) static int rtw_ops_sta_add(struct ieee80211_hw *hw,
			   struct ieee80211_vif *vif,
			   struct ieee80211_sta *sta)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_sta_info *si = (struct rtw_sta_info *)sta->drv_priv;
	int ret = 0;

	mutex_lock(&rtwdev->mutex);

	si->mac_id = rtw_acquire_macid(rtwdev);
	if (si->mac_id >= RTW_MAX_MAC_ID_NUM) {
		ret = -ENOSPC;
		goto out;
	}

	si->sta = sta;
	si->vif = vif;
	si->init_ra_lv = 1;
	ewma_rssi_init(&si->avg_rssi);

	rtw_update_sta_info(rtwdev, si);
	rtw_fw_media_status_report(rtwdev, si->mac_id, true);

	rtwdev->sta_cnt++;

	rtw_info(rtwdev, "sta %pM joined with macid %d\n",
		 sta->addr, si->mac_id);

out:
	mutex_unlock(&rtwdev->mutex);
	return ret;
}