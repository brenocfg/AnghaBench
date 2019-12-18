#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_vif {TYPE_1__* queue_params; scalar_t__ he_ru_2mhz_block; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; TYPE_4__* fw; } ;
struct iwl_he_sta_context_cmd_v1 {int dummy; } ;
struct TYPE_14__ {void**** pkt_ext_qam_th; } ;
struct iwl_he_sta_context_cmd {int sta_id; void* frame_time_rts_th; int rand_alloc_ecwmin; int rand_alloc_ecwmax; int /*<<< orphan*/  flags; int /*<<< orphan*/  profile_periodicity; int /*<<< orphan*/  ema_ap; int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  max_bssid_indicator; int /*<<< orphan*/  ref_bssid_addr; TYPE_2__* trig_based_txf; TYPE_7__ pkt_ext; int /*<<< orphan*/  htc_flags; int /*<<< orphan*/  htc_trig_based_pkt_ext; int /*<<< orphan*/  bss_color; int /*<<< orphan*/  tid_limit; } ;
struct iwl_he_pkt_ext {int*** pkt_ext_qam_th; } ;
struct TYPE_10__ {int frame_time_rts_th; int uora_ocw_range; int /*<<< orphan*/  profile_periodicity; int /*<<< orphan*/  ema_ap; int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  bssid_indicator; int /*<<< orphan*/  transmitter_bssid; scalar_t__ nontransmitted; scalar_t__ uora_exists; scalar_t__ ack_enabled; scalar_t__ multi_sta_back_32bit; int /*<<< orphan*/  htc_trig_based_pkt_ext; int /*<<< orphan*/  bss_color; } ;
struct ieee80211_vif {TYPE_3__ bss_conf; } ;
struct TYPE_12__ {int* mac_cap_info; int* phy_cap_info; } ;
struct TYPE_13__ {int* ppe_thres; TYPE_5__ he_cap_elem; int /*<<< orphan*/  has_he; } ;
struct ieee80211_sta {TYPE_6__ he_cap; } ;
struct ieee80211_he_mu_edca_param_ac_rec {int ecw_min_max; int aifsn; int mu_edca_timer; } ;
typedef  int /*<<< orphan*/  sta_ctxt_cmd ;
struct TYPE_11__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_9__ {void* mu_time; void* aifsn; void* cwmax; void* cwmin; } ;
struct TYPE_8__ {int /*<<< orphan*/  mu_edca; struct ieee80211_he_mu_edca_param_ac_rec mu_edca_param_rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PATH_GROUP ; 
 int IEEE80211_HE_MAC_CAP0_HTC_HE ; 
 int IEEE80211_HE_MAC_CAP1_LINK_ADAPTATION ; 
 int IEEE80211_HE_MAC_CAP2_BSR ; 
 int IEEE80211_HE_MAC_CAP2_LINK_ADAPTATION ; 
 int IEEE80211_HE_MAC_CAP3_OMI_CONTROL ; 
 int IEEE80211_HE_MAC_CAP4_BQR ; 
 int IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT ; 
#define  IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_0US 130 
#define  IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_16US 129 
#define  IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_8US 128 
 int IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_MASK ; 
 int IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_RESERVED ; 
 int IEEE80211_NUM_ACS ; 
 scalar_t__ IEEE80211_PPE_THRES_INFO_PPET_SIZE ; 
 int IEEE80211_PPE_THRES_NSS_MASK ; 
 int IEEE80211_PPE_THRES_RU_INDEX_BITMASK_MASK ; 
 int IEEE80211_PPE_THRES_RU_INDEX_BITMASK_POS ; 
 scalar_t__ IS_ERR (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_HE_HTC_BQR_SUPP ; 
 int /*<<< orphan*/  IWL_HE_HTC_BSR_SUPP ; 
 int /*<<< orphan*/  IWL_HE_HTC_LINK_ADAP_BOTH ; 
 int /*<<< orphan*/  IWL_HE_HTC_LINK_ADAP_UNSOLICITED ; 
 int /*<<< orphan*/  IWL_HE_HTC_OMI_SUPP ; 
 int /*<<< orphan*/  IWL_HE_HTC_SUPPORT ; 
 int IWL_HE_PKT_EXT_BPSK ; 
 int IWL_HE_PKT_EXT_NONE ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_mvm*,char*,int,int) ; 
 int /*<<< orphan*/  IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_MBSSID_HE ; 
 int MAX_HE_CHANNEL_BW_INDX ; 
 int MAX_HE_SUPP_NSS ; 
 int /*<<< orphan*/  STA_CTXT_HE_32BIT_BA_BITMAP ; 
 int /*<<< orphan*/  STA_CTXT_HE_ACK_ENABLED ; 
 int /*<<< orphan*/  STA_CTXT_HE_MU_EDCA_CW ; 
 int /*<<< orphan*/  STA_CTXT_HE_PACKET_EXT ; 
 int /*<<< orphan*/  STA_CTXT_HE_REF_BSSID_VALID ; 
 int /*<<< orphan*/  STA_CTXT_HE_RU_2MHZ_BLOCK ; 
 int /*<<< orphan*/  STA_CTXT_HE_TRIG_RND_ALLOC ; 
 int /*<<< orphan*/  STA_HE_CTXT_CMD ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* iwl_mvm_he_get_ppe_val (int*,int) ; 
 int iwl_mvm_mac80211_ac_to_ucode_ac (int) ; 
 scalar_t__ iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_he_sta_context_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int,int) ; 
 struct ieee80211_sta* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void iwl_mvm_cfg_he_sta(struct iwl_mvm *mvm,
			       struct ieee80211_vif *vif, u8 sta_id)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_he_sta_context_cmd sta_ctxt_cmd = {
		.sta_id = sta_id,
		.tid_limit = IWL_MAX_TID_COUNT,
		.bss_color = vif->bss_conf.bss_color,
		.htc_trig_based_pkt_ext = vif->bss_conf.htc_trig_based_pkt_ext,
		.frame_time_rts_th =
			cpu_to_le16(vif->bss_conf.frame_time_rts_th),
	};
	int size = fw_has_api(&mvm->fw->ucode_capa,
			      IWL_UCODE_TLV_API_MBSSID_HE) ?
		   sizeof(sta_ctxt_cmd) :
		   sizeof(struct iwl_he_sta_context_cmd_v1);
	struct ieee80211_sta *sta;
	u32 flags;
	int i;

	rcu_read_lock();

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_ctxt_cmd.sta_id]);
	if (IS_ERR(sta)) {
		rcu_read_unlock();
		WARN(1, "Can't find STA to configure HE\n");
		return;
	}

	if (!sta->he_cap.has_he) {
		rcu_read_unlock();
		return;
	}

	flags = 0;

	/* Block 26-tone RU OFDMA transmissions */
	if (mvmvif->he_ru_2mhz_block)
		flags |= STA_CTXT_HE_RU_2MHZ_BLOCK;

	/* HTC flags */
	if (sta->he_cap.he_cap_elem.mac_cap_info[0] &
	    IEEE80211_HE_MAC_CAP0_HTC_HE)
		sta_ctxt_cmd.htc_flags |= cpu_to_le32(IWL_HE_HTC_SUPPORT);
	if ((sta->he_cap.he_cap_elem.mac_cap_info[1] &
	      IEEE80211_HE_MAC_CAP1_LINK_ADAPTATION) ||
	    (sta->he_cap.he_cap_elem.mac_cap_info[2] &
	      IEEE80211_HE_MAC_CAP2_LINK_ADAPTATION)) {
		u8 link_adap =
			((sta->he_cap.he_cap_elem.mac_cap_info[2] &
			  IEEE80211_HE_MAC_CAP2_LINK_ADAPTATION) << 1) +
			 (sta->he_cap.he_cap_elem.mac_cap_info[1] &
			  IEEE80211_HE_MAC_CAP1_LINK_ADAPTATION);

		if (link_adap == 2)
			sta_ctxt_cmd.htc_flags |=
				cpu_to_le32(IWL_HE_HTC_LINK_ADAP_UNSOLICITED);
		else if (link_adap == 3)
			sta_ctxt_cmd.htc_flags |=
				cpu_to_le32(IWL_HE_HTC_LINK_ADAP_BOTH);
	}
	if (sta->he_cap.he_cap_elem.mac_cap_info[2] & IEEE80211_HE_MAC_CAP2_BSR)
		sta_ctxt_cmd.htc_flags |= cpu_to_le32(IWL_HE_HTC_BSR_SUPP);
	if (sta->he_cap.he_cap_elem.mac_cap_info[3] &
	    IEEE80211_HE_MAC_CAP3_OMI_CONTROL)
		sta_ctxt_cmd.htc_flags |= cpu_to_le32(IWL_HE_HTC_OMI_SUPP);
	if (sta->he_cap.he_cap_elem.mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_BQR)
		sta_ctxt_cmd.htc_flags |= cpu_to_le32(IWL_HE_HTC_BQR_SUPP);

	/*
	 * Initialize the PPE thresholds to "None" (7), as described in Table
	 * 9-262ac of 80211.ax/D3.0.
	 */
	memset(&sta_ctxt_cmd.pkt_ext, 7, sizeof(sta_ctxt_cmd.pkt_ext));

	/* If PPE Thresholds exist, parse them into a FW-familiar format. */
	if (sta->he_cap.he_cap_elem.phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT) {
		u8 nss = (sta->he_cap.ppe_thres[0] &
			  IEEE80211_PPE_THRES_NSS_MASK) + 1;
		u8 ru_index_bitmap =
			(sta->he_cap.ppe_thres[0] &
			 IEEE80211_PPE_THRES_RU_INDEX_BITMASK_MASK) >>
			IEEE80211_PPE_THRES_RU_INDEX_BITMASK_POS;
		u8 *ppe = &sta->he_cap.ppe_thres[0];
		u8 ppe_pos_bit = 7; /* Starting after PPE header */

		/*
		 * FW currently supports only nss == MAX_HE_SUPP_NSS
		 *
		 * If nss > MAX: we can ignore values we don't support
		 * If nss < MAX: we can set zeros in other streams
		 */
		if (nss > MAX_HE_SUPP_NSS) {
			IWL_INFO(mvm, "Got NSS = %d - trimming to %d\n", nss,
				 MAX_HE_SUPP_NSS);
			nss = MAX_HE_SUPP_NSS;
		}

		for (i = 0; i < nss; i++) {
			u8 ru_index_tmp = ru_index_bitmap << 1;
			u8 bw;

			for (bw = 0; bw < MAX_HE_CHANNEL_BW_INDX; bw++) {
				ru_index_tmp >>= 1;
				if (!(ru_index_tmp & 1))
					continue;

				sta_ctxt_cmd.pkt_ext.pkt_ext_qam_th[i][bw][1] =
					iwl_mvm_he_get_ppe_val(ppe,
							       ppe_pos_bit);
				ppe_pos_bit +=
					IEEE80211_PPE_THRES_INFO_PPET_SIZE;
				sta_ctxt_cmd.pkt_ext.pkt_ext_qam_th[i][bw][0] =
					iwl_mvm_he_get_ppe_val(ppe,
							       ppe_pos_bit);
				ppe_pos_bit +=
					IEEE80211_PPE_THRES_INFO_PPET_SIZE;
			}
		}

		flags |= STA_CTXT_HE_PACKET_EXT;
	} else if ((sta->he_cap.he_cap_elem.phy_cap_info[9] &
		    IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_MASK) !=
		  IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_RESERVED) {
		int low_th = -1;
		int high_th = -1;

		/* Take the PPE thresholds from the nominal padding info */
		switch (sta->he_cap.he_cap_elem.phy_cap_info[9] &
			IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_MASK) {
		case IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_0US:
			low_th = IWL_HE_PKT_EXT_NONE;
			high_th = IWL_HE_PKT_EXT_NONE;
			break;
		case IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_8US:
			low_th = IWL_HE_PKT_EXT_BPSK;
			high_th = IWL_HE_PKT_EXT_NONE;
			break;
		case IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_16US:
			low_th = IWL_HE_PKT_EXT_NONE;
			high_th = IWL_HE_PKT_EXT_BPSK;
			break;
		}

		/* Set the PPE thresholds accordingly */
		if (low_th >= 0 && high_th >= 0) {
			struct iwl_he_pkt_ext *pkt_ext =
				(struct iwl_he_pkt_ext *)&sta_ctxt_cmd.pkt_ext;

			for (i = 0; i < MAX_HE_SUPP_NSS; i++) {
				u8 bw;

				for (bw = 0; bw < MAX_HE_CHANNEL_BW_INDX;
				     bw++) {
					pkt_ext->pkt_ext_qam_th[i][bw][0] =
						low_th;
					pkt_ext->pkt_ext_qam_th[i][bw][1] =
						high_th;
				}
			}

			flags |= STA_CTXT_HE_PACKET_EXT;
		}
	}
	rcu_read_unlock();

	/* Mark MU EDCA as enabled, unless none detected on some AC */
	flags |= STA_CTXT_HE_MU_EDCA_CW;
	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		struct ieee80211_he_mu_edca_param_ac_rec *mu_edca =
			&mvmvif->queue_params[i].mu_edca_param_rec;
		u8 ac = iwl_mvm_mac80211_ac_to_ucode_ac(i);

		if (!mvmvif->queue_params[i].mu_edca) {
			flags &= ~STA_CTXT_HE_MU_EDCA_CW;
			break;
		}

		sta_ctxt_cmd.trig_based_txf[ac].cwmin =
			cpu_to_le16(mu_edca->ecw_min_max & 0xf);
		sta_ctxt_cmd.trig_based_txf[ac].cwmax =
			cpu_to_le16((mu_edca->ecw_min_max & 0xf0) >> 4);
		sta_ctxt_cmd.trig_based_txf[ac].aifsn =
			cpu_to_le16(mu_edca->aifsn);
		sta_ctxt_cmd.trig_based_txf[ac].mu_time =
			cpu_to_le16(mu_edca->mu_edca_timer);
	}

	if (vif->bss_conf.multi_sta_back_32bit)
		flags |= STA_CTXT_HE_32BIT_BA_BITMAP;

	if (vif->bss_conf.ack_enabled)
		flags |= STA_CTXT_HE_ACK_ENABLED;

	if (vif->bss_conf.uora_exists) {
		flags |= STA_CTXT_HE_TRIG_RND_ALLOC;

		sta_ctxt_cmd.rand_alloc_ecwmin =
			vif->bss_conf.uora_ocw_range & 0x7;
		sta_ctxt_cmd.rand_alloc_ecwmax =
			(vif->bss_conf.uora_ocw_range >> 3) & 0x7;
	}

	if (vif->bss_conf.nontransmitted) {
		flags |= STA_CTXT_HE_REF_BSSID_VALID;
		ether_addr_copy(sta_ctxt_cmd.ref_bssid_addr,
				vif->bss_conf.transmitter_bssid);
		sta_ctxt_cmd.max_bssid_indicator =
			vif->bss_conf.bssid_indicator;
		sta_ctxt_cmd.bssid_index = vif->bss_conf.bssid_index;
		sta_ctxt_cmd.ema_ap = vif->bss_conf.ema_ap;
		sta_ctxt_cmd.profile_periodicity =
			vif->bss_conf.profile_periodicity;
	}

	sta_ctxt_cmd.flags = cpu_to_le32(flags);

	if (iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(STA_HE_CTXT_CMD,
						 DATA_PATH_GROUP, 0),
				 0, size, &sta_ctxt_cmd))
		IWL_ERR(mvm, "Failed to config FW to work HE!\n");
}