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
typedef  int u32 ;
struct ieee80211_sta {int uapsd_queues; scalar_t__ max_sp; int /*<<< orphan*/  addr; scalar_t__ wme; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int IEEE80211_WMM_IE_STA_QOSINFO_AC_BE ; 
 int IEEE80211_WMM_IE_STA_QOSINFO_AC_BK ; 
 int IEEE80211_WMM_IE_STA_QOSINFO_AC_VI ; 
 int IEEE80211_WMM_IE_STA_QOSINFO_AC_VO ; 
 scalar_t__ MAX_WMI_AP_PS_PEER_PARAM_MAX_SP ; 
 int /*<<< orphan*/  WMI_AP_PS_PEER_PARAM_AGEOUT_TIME ; 
 int /*<<< orphan*/  WMI_AP_PS_PEER_PARAM_MAX_SP ; 
 int /*<<< orphan*/  WMI_AP_PS_PEER_PARAM_UAPSD ; 
 int WMI_AP_PS_UAPSD_AC0_DELIVERY_EN ; 
 int WMI_AP_PS_UAPSD_AC0_TRIGGER_EN ; 
 int WMI_AP_PS_UAPSD_AC1_DELIVERY_EN ; 
 int WMI_AP_PS_UAPSD_AC1_TRIGGER_EN ; 
 int WMI_AP_PS_UAPSD_AC2_DELIVERY_EN ; 
 int WMI_AP_PS_UAPSD_AC2_TRIGGER_EN ; 
 int WMI_AP_PS_UAPSD_AC3_DELIVERY_EN ; 
 int WMI_AP_PS_UAPSD_AC3_TRIGGER_EN ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_set_ap_ps_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_peer_assoc_qos_ap(struct ath10k *ar,
				    struct ath10k_vif *arvif,
				    struct ieee80211_sta *sta)
{
	u32 uapsd = 0;
	u32 max_sp = 0;
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	if (sta->wme && sta->uapsd_queues) {
		ath10k_dbg(ar, ATH10K_DBG_MAC, "mac uapsd_queues 0x%x max_sp %d\n",
			   sta->uapsd_queues, sta->max_sp);

		if (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
			uapsd |= WMI_AP_PS_UAPSD_AC3_DELIVERY_EN |
				 WMI_AP_PS_UAPSD_AC3_TRIGGER_EN;
		if (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI)
			uapsd |= WMI_AP_PS_UAPSD_AC2_DELIVERY_EN |
				 WMI_AP_PS_UAPSD_AC2_TRIGGER_EN;
		if (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)
			uapsd |= WMI_AP_PS_UAPSD_AC1_DELIVERY_EN |
				 WMI_AP_PS_UAPSD_AC1_TRIGGER_EN;
		if (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE)
			uapsd |= WMI_AP_PS_UAPSD_AC0_DELIVERY_EN |
				 WMI_AP_PS_UAPSD_AC0_TRIGGER_EN;

		if (sta->max_sp < MAX_WMI_AP_PS_PEER_PARAM_MAX_SP)
			max_sp = sta->max_sp;

		ret = ath10k_wmi_set_ap_ps_param(ar, arvif->vdev_id,
						 sta->addr,
						 WMI_AP_PS_PEER_PARAM_UAPSD,
						 uapsd);
		if (ret) {
			ath10k_warn(ar, "failed to set ap ps peer param uapsd for vdev %i: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}

		ret = ath10k_wmi_set_ap_ps_param(ar, arvif->vdev_id,
						 sta->addr,
						 WMI_AP_PS_PEER_PARAM_MAX_SP,
						 max_sp);
		if (ret) {
			ath10k_warn(ar, "failed to set ap ps peer param max sp for vdev %i: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}

		/* TODO setup this based on STA listen interval and
		 * beacon interval. Currently we don't know
		 * sta->listen_interval - mac80211 patch required.
		 * Currently use 10 seconds
		 */
		ret = ath10k_wmi_set_ap_ps_param(ar, arvif->vdev_id, sta->addr,
						 WMI_AP_PS_PEER_PARAM_AGEOUT_TIME,
						 10);
		if (ret) {
			ath10k_warn(ar, "failed to set ap ps peer param ageout time for vdev %i: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}
	}

	return 0;
}