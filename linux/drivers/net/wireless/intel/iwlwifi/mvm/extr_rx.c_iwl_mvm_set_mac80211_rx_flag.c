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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_mvm {int /*<<< orphan*/  monitor_on; TYPE_1__* fw; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CCMP_HDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_TKIP_IV_LEN ; 
 int /*<<< orphan*/  IEEE80211_WEP_IV_LEN ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_DEPRECATE_TTAK ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int RX_MPDU_RES_STATUS_ICV_OK ; 
 int RX_MPDU_RES_STATUS_MIC_OK ; 
#define  RX_MPDU_RES_STATUS_SEC_CCM_ENC 131 
 int RX_MPDU_RES_STATUS_SEC_ENC_ERR ; 
 int RX_MPDU_RES_STATUS_SEC_ENC_MSK ; 
#define  RX_MPDU_RES_STATUS_SEC_EXT_ENC 130 
 int RX_MPDU_RES_STATUS_SEC_NO_ENC ; 
#define  RX_MPDU_RES_STATUS_SEC_TKIP_ENC 129 
#define  RX_MPDU_RES_STATUS_SEC_WEP_ENC 128 
 int RX_MPDU_RES_STATUS_TTAK_OK ; 
 int /*<<< orphan*/  fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_has_protected (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iwl_mvm_set_mac80211_rx_flag(struct iwl_mvm *mvm,
					struct ieee80211_hdr *hdr,
					struct ieee80211_rx_status *stats,
					u32 rx_pkt_status,
					u8 *crypt_len)
{
	if (!ieee80211_has_protected(hdr->frame_control) ||
	    (rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) ==
			     RX_MPDU_RES_STATUS_SEC_NO_ENC)
		return 0;

	/* packet was encrypted with unknown alg */
	if ((rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) ==
					RX_MPDU_RES_STATUS_SEC_ENC_ERR)
		return 0;

	switch (rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) {
	case RX_MPDU_RES_STATUS_SEC_CCM_ENC:
		/* alg is CCM: check MIC only */
		if (!(rx_pkt_status & RX_MPDU_RES_STATUS_MIC_OK))
			return -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		*crypt_len = IEEE80211_CCMP_HDR_LEN;
		return 0;

	case RX_MPDU_RES_STATUS_SEC_TKIP_ENC:
		/* Don't drop the frame and decrypt it in SW */
		if (!fw_has_api(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_API_DEPRECATE_TTAK) &&
		    !(rx_pkt_status & RX_MPDU_RES_STATUS_TTAK_OK))
			return 0;
		*crypt_len = IEEE80211_TKIP_IV_LEN;
		/* fall through */

	case RX_MPDU_RES_STATUS_SEC_WEP_ENC:
		if (!(rx_pkt_status & RX_MPDU_RES_STATUS_ICV_OK))
			return -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		if ((rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) ==
				RX_MPDU_RES_STATUS_SEC_WEP_ENC)
			*crypt_len = IEEE80211_WEP_IV_LEN;
		return 0;

	case RX_MPDU_RES_STATUS_SEC_EXT_ENC:
		if (!(rx_pkt_status & RX_MPDU_RES_STATUS_MIC_OK))
			return -1;
		stats->flag |= RX_FLAG_DECRYPTED;
		return 0;

	default:
		/* Expected in monitor (not having the keys) */
		if (!mvm->monitor_on)
			IWL_ERR(mvm, "Unhandled alg: 0x%x\n", rx_pkt_status);
	}

	return 0;
}