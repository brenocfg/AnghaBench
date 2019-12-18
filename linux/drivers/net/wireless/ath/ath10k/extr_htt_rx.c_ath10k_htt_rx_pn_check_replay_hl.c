#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union htt_rx_pn_t {int /*<<< orphan*/  pn48; int /*<<< orphan*/  member_0; } ;
typedef  size_t u32 ;
struct TYPE_5__ {size_t info0; int /*<<< orphan*/  info1; } ;
struct TYPE_4__ {int flags; } ;
struct htt_rx_indication_hl {TYPE_2__ hdr; int /*<<< orphan*/ * mpdu_ranges; TYPE_1__ fw_desc; } ;
struct htt_hl_rx_desc {int /*<<< orphan*/  info; } ;
struct ath10k_peer {int* tids_last_pn_valid; TYPE_3__* rx_pn; union htt_rx_pn_t* tids_last_pn; } ;
struct ath10k {int /*<<< orphan*/  data_lock; } ;
typedef  enum htt_txrx_sec_cast_type { ____Placeholder_htt_txrx_sec_cast_type } htt_txrx_sec_cast_type ;
typedef  enum htt_security_types { ____Placeholder_htt_security_types } htt_security_types ;
struct TYPE_6__ {int sec_type; int /*<<< orphan*/  pn_len; } ;

/* Variables and functions */
 int FW_RX_DESC_FLAGS_FIRST_MSDU ; 
 int /*<<< orphan*/  HTT_RX_DESC_HL_INFO_ENCRYPTED ; 
 int /*<<< orphan*/  HTT_RX_DESC_HL_INFO_MCAST_BCAST ; 
 int /*<<< orphan*/  HTT_RX_INDICATION_INFO0_EXT_TID ; 
 int /*<<< orphan*/  HTT_RX_INDICATION_INFO1_NUM_MPDU_RANGES ; 
 int HTT_SECURITY_AES_CCMP ; 
 int HTT_SECURITY_TKIP ; 
 int HTT_SECURITY_TKIP_NOMIC ; 
 int HTT_TXRX_SEC_MCAST ; 
 int HTT_TXRX_SEC_UCAST ; 
 int MS (size_t,int /*<<< orphan*/ ) ; 
 size_t __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_htt_rx_mpdu_desc_pn_hl (struct htt_hl_rx_desc*,union htt_rx_pn_t*,int /*<<< orphan*/ ) ; 
 int ath10k_htt_rx_pn_cmp48 (union htt_rx_pn_t*,union htt_rx_pn_t*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath10k_htt_rx_pn_check_replay_hl(struct ath10k *ar,
					     struct ath10k_peer *peer,
					     struct htt_rx_indication_hl *rx)
{
	bool last_pn_valid, pn_invalid = false;
	enum htt_txrx_sec_cast_type sec_index;
	enum htt_security_types sec_type;
	union htt_rx_pn_t new_pn = {0};
	struct htt_hl_rx_desc *rx_desc;
	union htt_rx_pn_t *last_pn;
	u32 rx_desc_info, tid;
	int num_mpdu_ranges;

	lockdep_assert_held(&ar->data_lock);

	if (!peer)
		return false;

	if (!(rx->fw_desc.flags & FW_RX_DESC_FLAGS_FIRST_MSDU))
		return false;

	num_mpdu_ranges = MS(__le32_to_cpu(rx->hdr.info1),
			     HTT_RX_INDICATION_INFO1_NUM_MPDU_RANGES);

	rx_desc = (struct htt_hl_rx_desc *)&rx->mpdu_ranges[num_mpdu_ranges];
	rx_desc_info = __le32_to_cpu(rx_desc->info);

	if (!MS(rx_desc_info, HTT_RX_DESC_HL_INFO_ENCRYPTED))
		return false;

	tid = MS(rx->hdr.info0, HTT_RX_INDICATION_INFO0_EXT_TID);
	last_pn_valid = peer->tids_last_pn_valid[tid];
	last_pn = &peer->tids_last_pn[tid];

	if (MS(rx_desc_info, HTT_RX_DESC_HL_INFO_MCAST_BCAST))
		sec_index = HTT_TXRX_SEC_MCAST;
	else
		sec_index = HTT_TXRX_SEC_UCAST;

	sec_type = peer->rx_pn[sec_index].sec_type;
	ath10k_htt_rx_mpdu_desc_pn_hl(rx_desc, &new_pn, peer->rx_pn[sec_index].pn_len);

	if (sec_type != HTT_SECURITY_AES_CCMP &&
	    sec_type != HTT_SECURITY_TKIP &&
	    sec_type != HTT_SECURITY_TKIP_NOMIC)
		return false;

	if (last_pn_valid)
		pn_invalid = ath10k_htt_rx_pn_cmp48(&new_pn, last_pn);
	else
		peer->tids_last_pn_valid[tid] = 1;

	if (!pn_invalid)
		last_pn->pn48 = new_pn.pn48;

	return pn_invalid;
}