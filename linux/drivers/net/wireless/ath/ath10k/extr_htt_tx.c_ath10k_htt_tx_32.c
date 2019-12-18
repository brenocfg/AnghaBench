#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int len; scalar_t__ ip_summed; TYPE_12__* data; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct htt_msdu_ext_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  frags; } ;
struct TYPE_22__ {void* len; void* paddr; } ;
struct TYPE_20__ {void* len_16; int /*<<< orphan*/  paddr_hi; void* paddr_lo; } ;
struct htt_data_tx_desc_frag {TYPE_4__ dword_addr; TYPE_2__ tword_addr; } ;
struct device {int dummy; } ;
struct ath10k_skb_cb {int flags; int paddr; } ;
struct TYPE_18__ {size_t eid; scalar_t__ flags; void* len; } ;
struct TYPE_25__ {void* freq; void* peerid; } ;
struct TYPE_26__ {int flags0; void* peerid; TYPE_7__ offchan_tx; void* frags_paddr; void* id; void* len; void* flags1; } ;
struct TYPE_24__ {int /*<<< orphan*/  msg_type; } ;
struct ath10k_htt_txbuf_32 {TYPE_12__ htc_hdr; TYPE_8__ cmd_tx; TYPE_6__ cmd_hdr; struct htt_data_tx_desc_frag* frags; } ;
struct TYPE_21__ {int /*<<< orphan*/  paddr; struct htt_msdu_ext_desc* vaddr_desc_32; } ;
struct TYPE_17__ {int paddr; struct ath10k_htt_txbuf_32* vaddr_txbuff_32; } ;
struct ath10k_htt {size_t eid; struct ath10k* ar; TYPE_3__ frag_desc; TYPE_11__ txbuf; int /*<<< orphan*/  prefetch_len; } ;
struct ath10k_hif_sg_item {int paddr; int len; TYPE_12__* vaddr; int /*<<< orphan*/ * transfer_context; scalar_t__ transfer_id; } ;
struct TYPE_16__ {TYPE_9__* endpoint; } ;
struct TYPE_23__ {scalar_t__ continuous_frag_desc; } ;
struct TYPE_19__ {int roc_freq; } ;
struct ath10k {TYPE_10__ htc; TYPE_5__ hw_params; int /*<<< orphan*/  dev_flags; TYPE_1__ scan; struct device* dev; } ;
typedef  enum ath10k_hw_txrx_mode { ____Placeholder_ath10k_hw_txrx_mode } ath10k_hw_txrx_mode ;
struct TYPE_27__ {int /*<<< orphan*/  ul_pipe_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ath10k_hif_sg_item*) ; 
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 int /*<<< orphan*/  ATH10K_DBG_HTT_DUMP ; 
 int /*<<< orphan*/  ATH10K_FLAG_RAW_MODE ; 
#define  ATH10K_HW_TXRX_ETHERNET 131 
#define  ATH10K_HW_TXRX_MGMT 130 
#define  ATH10K_HW_TXRX_NATIVE_WIFI 129 
#define  ATH10K_HW_TXRX_RAW 128 
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 int ATH10K_SKB_F_NO_HWCRYPT ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT ; 
 int HTT_DATA_TX_DESC_FLAGS0_NO_ENCRYPT ; 
 int /*<<< orphan*/  HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE ; 
 int HTT_DATA_TX_DESC_FLAGS1_CKSUM_L3_OFFLOAD ; 
 int HTT_DATA_TX_DESC_FLAGS1_CKSUM_L4_OFFLOAD ; 
 int /*<<< orphan*/  HTT_DATA_TX_DESC_FLAGS1_EXT_TID ; 
 int HTT_DATA_TX_DESC_FLAGS1_POSTPONED ; 
 int /*<<< orphan*/  HTT_DATA_TX_DESC_FLAGS1_VDEV_ID ; 
 int /*<<< orphan*/  HTT_H2T_MSG_TYPE_TX_FRM ; 
 int HTT_INVALID_PEERID ; 
 int /*<<< orphan*/  HTT_MSDU_CHECKSUM_ENABLE ; 
 int /*<<< orphan*/  IEEE80211_CCMP_MIC_LEN ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_TX_OFFCHAN ; 
 int SM (int const,int /*<<< orphan*/ ) ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int,int,int,int*,int*,int,int,int) ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,TYPE_12__*,int) ; 
 int ath10k_hif_tx_sg (struct ath10k*,int /*<<< orphan*/ ,struct ath10k_hif_sg_item*,int /*<<< orphan*/ ) ; 
 int ath10k_htt_tx_alloc_msdu_id (struct ath10k_htt*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_htt_tx_free_msdu_id (struct ath10k_htt*,int) ; 
 int ath10k_htt_tx_get_tid (struct sk_buff*,int) ; 
 int ath10k_htt_tx_get_vdev_id (struct ath10k*,struct sk_buff*) ; 
 scalar_t__ ath10k_mac_tx_frm_has_freq (struct ath10k*) ; 
 int dma_map_single (struct device*,TYPE_12__*,int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_action (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_disassoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct htt_msdu_ext_desc*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ath10k_htt_tx (struct ath10k*,int,int,int,int) ; 
 int /*<<< orphan*/  trace_ath10k_tx_hdr (struct ath10k*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  trace_ath10k_tx_payload (struct ath10k*,TYPE_12__*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ath10k_htt_tx_32(struct ath10k_htt *htt,
			    enum ath10k_hw_txrx_mode txmode,
			    struct sk_buff *msdu)
{
	struct ath10k *ar = htt->ar;
	struct device *dev = ar->dev;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)msdu->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(msdu);
	struct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	struct ath10k_hif_sg_item sg_items[2];
	struct ath10k_htt_txbuf_32 *txbuf;
	struct htt_data_tx_desc_frag *frags;
	bool is_eth = (txmode == ATH10K_HW_TXRX_ETHERNET);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(ar, msdu);
	u8 tid = ath10k_htt_tx_get_tid(msdu, is_eth);
	int prefetch_len;
	int res;
	u8 flags0 = 0;
	u16 msdu_id, flags1 = 0;
	u16 freq = 0;
	u32 frags_paddr = 0;
	u32 txbuf_paddr;
	struct htt_msdu_ext_desc *ext_desc = NULL;
	struct htt_msdu_ext_desc *ext_desc_t = NULL;

	res = ath10k_htt_tx_alloc_msdu_id(htt, msdu);
	if (res < 0)
		goto err;

	msdu_id = res;

	prefetch_len = min(htt->prefetch_len, msdu->len);
	prefetch_len = roundup(prefetch_len, 4);

	txbuf = htt->txbuf.vaddr_txbuff_32 + msdu_id;
	txbuf_paddr = htt->txbuf.paddr +
		      (sizeof(struct ath10k_htt_txbuf_32) * msdu_id);

	if ((ieee80211_is_action(hdr->frame_control) ||
	     ieee80211_is_deauth(hdr->frame_control) ||
	     ieee80211_is_disassoc(hdr->frame_control)) &&
	     ieee80211_has_protected(hdr->frame_control)) {
		skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
	} else if (!(skb_cb->flags & ATH10K_SKB_F_NO_HWCRYPT) &&
		   txmode == ATH10K_HW_TXRX_RAW &&
		   ieee80211_has_protected(hdr->frame_control)) {
		skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
	}

	skb_cb->paddr = dma_map_single(dev, msdu->data, msdu->len,
				       DMA_TO_DEVICE);
	res = dma_mapping_error(dev, skb_cb->paddr);
	if (res) {
		res = -EIO;
		goto err_free_msdu_id;
	}

	if (unlikely(info->flags & IEEE80211_TX_CTL_TX_OFFCHAN))
		freq = ar->scan.roc_freq;

	switch (txmode) {
	case ATH10K_HW_TXRX_RAW:
	case ATH10K_HW_TXRX_NATIVE_WIFI:
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT;
		/* fall through */
	case ATH10K_HW_TXRX_ETHERNET:
		if (ar->hw_params.continuous_frag_desc) {
			ext_desc_t = htt->frag_desc.vaddr_desc_32;
			memset(&ext_desc_t[msdu_id], 0,
			       sizeof(struct htt_msdu_ext_desc));
			frags = (struct htt_data_tx_desc_frag *)
				&ext_desc_t[msdu_id].frags;
			ext_desc = &ext_desc_t[msdu_id];
			frags[0].tword_addr.paddr_lo =
				__cpu_to_le32(skb_cb->paddr);
			frags[0].tword_addr.paddr_hi = 0;
			frags[0].tword_addr.len_16 = __cpu_to_le16(msdu->len);

			frags_paddr =  htt->frag_desc.paddr +
				(sizeof(struct htt_msdu_ext_desc) * msdu_id);
		} else {
			frags = txbuf->frags;
			frags[0].dword_addr.paddr =
				__cpu_to_le32(skb_cb->paddr);
			frags[0].dword_addr.len = __cpu_to_le32(msdu->len);
			frags[1].dword_addr.paddr = 0;
			frags[1].dword_addr.len = 0;

			frags_paddr = txbuf_paddr;
		}
		flags0 |= SM(txmode, HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE);
		break;
	case ATH10K_HW_TXRX_MGMT:
		flags0 |= SM(ATH10K_HW_TXRX_MGMT,
			     HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE);
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT;

		frags_paddr = skb_cb->paddr;
		break;
	}

	/* Normally all commands go through HTC which manages tx credits for
	 * each endpoint and notifies when tx is completed.
	 *
	 * HTT endpoint is creditless so there's no need to care about HTC
	 * flags. In that case it is trivial to fill the HTC header here.
	 *
	 * MSDU transmission is considered completed upon HTT event. This
	 * implies no relevant resources can be freed until after the event is
	 * received. That's why HTC tx completion handler itself is ignored by
	 * setting NULL to transfer_context for all sg items.
	 *
	 * There is simply no point in pushing HTT TX_FRM through HTC tx path
	 * as it's a waste of resources. By bypassing HTC it is possible to
	 * avoid extra memory allocations, compress data structures and thus
	 * improve performance.
	 */

	txbuf->htc_hdr.eid = htt->eid;
	txbuf->htc_hdr.len = __cpu_to_le16(sizeof(txbuf->cmd_hdr) +
					   sizeof(txbuf->cmd_tx) +
					   prefetch_len);
	txbuf->htc_hdr.flags = 0;

	if (skb_cb->flags & ATH10K_SKB_F_NO_HWCRYPT)
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_NO_ENCRYPT;

	flags1 |= SM((u16)vdev_id, HTT_DATA_TX_DESC_FLAGS1_VDEV_ID);
	flags1 |= SM((u16)tid, HTT_DATA_TX_DESC_FLAGS1_EXT_TID);
	if (msdu->ip_summed == CHECKSUM_PARTIAL &&
	    !test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags)) {
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_CKSUM_L3_OFFLOAD;
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_CKSUM_L4_OFFLOAD;
		if (ar->hw_params.continuous_frag_desc)
			ext_desc->flags |= HTT_MSDU_CHECKSUM_ENABLE;
	}

	/* Prevent firmware from sending up tx inspection requests. There's
	 * nothing ath10k can do with frames requested for inspection so force
	 * it to simply rely a regular tx completion with discard status.
	 */
	flags1 |= HTT_DATA_TX_DESC_FLAGS1_POSTPONED;

	txbuf->cmd_hdr.msg_type = HTT_H2T_MSG_TYPE_TX_FRM;
	txbuf->cmd_tx.flags0 = flags0;
	txbuf->cmd_tx.flags1 = __cpu_to_le16(flags1);
	txbuf->cmd_tx.len = __cpu_to_le16(msdu->len);
	txbuf->cmd_tx.id = __cpu_to_le16(msdu_id);
	txbuf->cmd_tx.frags_paddr = __cpu_to_le32(frags_paddr);
	if (ath10k_mac_tx_frm_has_freq(ar)) {
		txbuf->cmd_tx.offchan_tx.peerid =
				__cpu_to_le16(HTT_INVALID_PEERID);
		txbuf->cmd_tx.offchan_tx.freq =
				__cpu_to_le16(freq);
	} else {
		txbuf->cmd_tx.peerid =
				__cpu_to_le32(HTT_INVALID_PEERID);
	}

	trace_ath10k_htt_tx(ar, msdu_id, msdu->len, vdev_id, tid);
	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt tx flags0 %hhu flags1 %hu len %d id %hu frags_paddr %pad, msdu_paddr %pad vdev %hhu tid %hhu freq %hu\n",
		   flags0, flags1, msdu->len, msdu_id, &frags_paddr,
		   &skb_cb->paddr, vdev_id, tid, freq);
	ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, NULL, "htt tx msdu: ",
			msdu->data, msdu->len);
	trace_ath10k_tx_hdr(ar, msdu->data, msdu->len);
	trace_ath10k_tx_payload(ar, msdu->data, msdu->len);

	sg_items[0].transfer_id = 0;
	sg_items[0].transfer_context = NULL;
	sg_items[0].vaddr = &txbuf->htc_hdr;
	sg_items[0].paddr = txbuf_paddr +
			    sizeof(txbuf->frags);
	sg_items[0].len = sizeof(txbuf->htc_hdr) +
			  sizeof(txbuf->cmd_hdr) +
			  sizeof(txbuf->cmd_tx);

	sg_items[1].transfer_id = 0;
	sg_items[1].transfer_context = NULL;
	sg_items[1].vaddr = msdu->data;
	sg_items[1].paddr = skb_cb->paddr;
	sg_items[1].len = prefetch_len;

	res = ath10k_hif_tx_sg(htt->ar,
			       htt->ar->htc.endpoint[htt->eid].ul_pipe_id,
			       sg_items, ARRAY_SIZE(sg_items));
	if (res)
		goto err_unmap_msdu;

	return 0;

err_unmap_msdu:
	dma_unmap_single(dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);
err_free_msdu_id:
	ath10k_htt_tx_free_msdu_id(htt, msdu_id);
err:
	return res;
}