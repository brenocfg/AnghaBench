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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct iwl_ba_window_status_notif {int /*<<< orphan*/ * start_seq_num; int /*<<< orphan*/ * bitmap; int /*<<< orphan*/ * mpdu_rx_count; int /*<<< orphan*/ * ra_tid; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 scalar_t__ BA_WINDOW_STATUS_STA_ID_MSK ; 
 scalar_t__ BA_WINDOW_STATUS_STA_ID_POS ; 
 scalar_t__ BA_WINDOW_STATUS_TID_MSK ; 
 scalar_t__ BA_WINDOW_STATUS_VALID_MSK ; 
 int BA_WINDOW_STREAMS_MAX ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 scalar_t__ WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  ieee80211_mark_rx_ba_filtered_frames (struct ieee80211_sta*,size_t,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int iwl_rx_packet_payload_len (struct iwl_rx_packet*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_window_status_notif(struct iwl_mvm *mvm,
				 struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_ba_window_status_notif *notif = (void *)pkt->data;
	int i;
	u32 pkt_len = iwl_rx_packet_payload_len(pkt);

	if (WARN_ONCE(pkt_len != sizeof(*notif),
		      "Received window status notification of wrong size (%u)\n",
		      pkt_len))
		return;

	rcu_read_lock();
	for (i = 0; i < BA_WINDOW_STREAMS_MAX; i++) {
		struct ieee80211_sta *sta;
		u8 sta_id, tid;
		u64 bitmap;
		u32 ssn;
		u16 ratid;
		u16 received_mpdu;

		ratid = le16_to_cpu(notif->ra_tid[i]);
		/* check that this TID is valid */
		if (!(ratid & BA_WINDOW_STATUS_VALID_MSK))
			continue;

		received_mpdu = le16_to_cpu(notif->mpdu_rx_count[i]);
		if (received_mpdu == 0)
			continue;

		tid = ratid & BA_WINDOW_STATUS_TID_MSK;
		/* get the station */
		sta_id = (ratid & BA_WINDOW_STATUS_STA_ID_MSK)
			 >> BA_WINDOW_STATUS_STA_ID_POS;
		sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);
		if (IS_ERR_OR_NULL(sta))
			continue;
		bitmap = le64_to_cpu(notif->bitmap[i]);
		ssn = le32_to_cpu(notif->start_seq_num[i]);

		/* update mac80211 with the bitmap for the reordering buffer */
		ieee80211_mark_rx_ba_filtered_frames(sta, tid, ssn, bitmap,
						     received_mpdu);
	}
	rcu_read_unlock();
}