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
struct rtw_vif {int net_type; int /*<<< orphan*/  bssid; scalar_t__ aid; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {TYPE_1__* ops; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  bssid; scalar_t__ assoc; scalar_t__ aid; } ;
typedef  enum rtw_net_type { ____Placeholder_rtw_net_type } rtw_net_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* phy_calibration ) (struct rtw_dev*) ;} ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BSSID ; 
 int /*<<< orphan*/  COEX_ASSOCIATE_FINISH ; 
 int PORT_SET_AID ; 
 int PORT_SET_BSSID ; 
 int PORT_SET_NET_TYPE ; 
 int /*<<< orphan*/  RSVD_NULL ; 
 int /*<<< orphan*/  RSVD_PS_POLL ; 
 int /*<<< orphan*/  RSVD_QOS_NULL ; 
 int RTW_NET_MGD_LINKED ; 
 int RTW_NET_NO_LINK ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_add_rsvd_page (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_coex_connect_notify (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_media_status_notify (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_fw_download_rsvd_page (struct rtw_dev*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  rtw_reset_rsvd_page (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_send_rsvd_page_h2c (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_vif_port_config (struct rtw_dev*,struct rtw_vif*,int) ; 
 int /*<<< orphan*/  stub1 (struct rtw_dev*) ; 

__attribute__((used)) static void rtw_ops_bss_info_changed(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif,
				     struct ieee80211_bss_conf *conf,
				     u32 changed)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_vif *rtwvif = (struct rtw_vif *)vif->drv_priv;
	u32 config = 0;

	mutex_lock(&rtwdev->mutex);

	if (changed & BSS_CHANGED_ASSOC) {
		struct rtw_chip_info *chip = rtwdev->chip;
		enum rtw_net_type net_type;

		if (conf->assoc) {
			rtw_coex_connect_notify(rtwdev, COEX_ASSOCIATE_FINISH);
			net_type = RTW_NET_MGD_LINKED;
			chip->ops->phy_calibration(rtwdev);

			rtwvif->aid = conf->aid;
			rtw_add_rsvd_page(rtwdev, RSVD_PS_POLL, true);
			rtw_add_rsvd_page(rtwdev, RSVD_QOS_NULL, true);
			rtw_add_rsvd_page(rtwdev, RSVD_NULL, true);
			rtw_fw_download_rsvd_page(rtwdev, vif);
			rtw_send_rsvd_page_h2c(rtwdev);
			rtw_coex_media_status_notify(rtwdev, conf->assoc);
		} else {
			net_type = RTW_NET_NO_LINK;
			rtwvif->aid = 0;
			rtw_reset_rsvd_page(rtwdev);
		}

		rtwvif->net_type = net_type;
		config |= PORT_SET_NET_TYPE;
		config |= PORT_SET_AID;
	}

	if (changed & BSS_CHANGED_BSSID) {
		ether_addr_copy(rtwvif->bssid, conf->bssid);
		config |= PORT_SET_BSSID;
	}

	if (changed & BSS_CHANGED_BEACON)
		rtw_fw_download_rsvd_page(rtwdev, vif);

	rtw_vif_port_config(rtwdev, rtwvif, config);

	mutex_unlock(&rtwdev->mutex);
}