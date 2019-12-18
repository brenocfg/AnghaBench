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
typedef  int u8 ;
typedef  int u16 ;
struct wmi_cac_event {size_t ac; scalar_t__ cac_indication; scalar_t__ status_code; int /*<<< orphan*/  tspec_suggestion; } ;
struct wmi {int* stream_exist_for_ac; int fat_pipe_exist; int /*<<< orphan*/  parent_dev; int /*<<< orphan*/  lock; } ;
struct ieee80211_tspec_ie {int /*<<< orphan*/  tsinfo; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; } ;
typedef  int /*<<< orphan*/  active_tsids ;

/* Variables and functions */
 scalar_t__ CAC_INDICATION_ADMISSION_RESP ; 
 scalar_t__ CAC_INDICATION_DELETE ; 
 scalar_t__ CAC_INDICATION_NO_RESP ; 
 int EINVAL ; 
 scalar_t__ IEEE80211_TSPEC_STATUS_ADMISS_ACCEPTED ; 
 int IEEE80211_WMM_IE_TSPEC_TID_MASK ; 
 int IEEE80211_WMM_IE_TSPEC_TID_SHIFT ; 
 size_t WMM_NUM_AC ; 
 int /*<<< orphan*/  ath6kl_err (char*,size_t) ; 
 int /*<<< orphan*/  ath6kl_indicate_tx_activity (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  ath6kl_wmi_delete_pstream_cmd (struct wmi*,int /*<<< orphan*/ ,size_t,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_wmi_cac_event_rx(struct wmi *wmi, u8 *datap, int len,
				   struct ath6kl_vif *vif)
{
	struct wmi_cac_event *reply;
	struct ieee80211_tspec_ie *ts;
	u16 active_tsids, tsinfo;
	u8 tsid, index;
	u8 ts_id;

	if (len < sizeof(struct wmi_cac_event))
		return -EINVAL;

	reply = (struct wmi_cac_event *) datap;
	if (reply->ac >= WMM_NUM_AC) {
		ath6kl_err("invalid AC: %d\n", reply->ac);
		return -EINVAL;
	}

	if ((reply->cac_indication == CAC_INDICATION_ADMISSION_RESP) &&
	    (reply->status_code != IEEE80211_TSPEC_STATUS_ADMISS_ACCEPTED)) {
		ts = (struct ieee80211_tspec_ie *) &(reply->tspec_suggestion);
		tsinfo = le16_to_cpu(ts->tsinfo);
		tsid = (tsinfo >> IEEE80211_WMM_IE_TSPEC_TID_SHIFT) &
			IEEE80211_WMM_IE_TSPEC_TID_MASK;

		ath6kl_wmi_delete_pstream_cmd(wmi, vif->fw_vif_idx,
					      reply->ac, tsid);
	} else if (reply->cac_indication == CAC_INDICATION_NO_RESP) {
		/*
		 * Following assumes that there is only one outstanding
		 * ADDTS request when this event is received
		 */
		spin_lock_bh(&wmi->lock);
		active_tsids = wmi->stream_exist_for_ac[reply->ac];
		spin_unlock_bh(&wmi->lock);

		for (index = 0; index < sizeof(active_tsids) * 8; index++) {
			if ((active_tsids >> index) & 1)
				break;
		}
		if (index < (sizeof(active_tsids) * 8))
			ath6kl_wmi_delete_pstream_cmd(wmi, vif->fw_vif_idx,
						      reply->ac, index);
	}

	/*
	 * Clear active tsids and Add missing handling
	 * for delete qos stream from AP
	 */
	else if (reply->cac_indication == CAC_INDICATION_DELETE) {
		ts = (struct ieee80211_tspec_ie *) &(reply->tspec_suggestion);
		tsinfo = le16_to_cpu(ts->tsinfo);
		ts_id = ((tsinfo >> IEEE80211_WMM_IE_TSPEC_TID_SHIFT) &
			 IEEE80211_WMM_IE_TSPEC_TID_MASK);

		spin_lock_bh(&wmi->lock);
		wmi->stream_exist_for_ac[reply->ac] &= ~(1 << ts_id);
		active_tsids = wmi->stream_exist_for_ac[reply->ac];
		spin_unlock_bh(&wmi->lock);

		/* Indicate stream inactivity to driver layer only if all tsids
		 * within this AC are deleted.
		 */
		if (!active_tsids) {
			ath6kl_indicate_tx_activity(wmi->parent_dev, reply->ac,
						    false);
			wmi->fat_pipe_exist &= ~(1 << reply->ac);
		}
	}

	return 0;
}