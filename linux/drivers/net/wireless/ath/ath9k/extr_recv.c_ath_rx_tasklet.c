#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_rx_status {int rs_datalen; int flag; int /*<<< orphan*/  rs_tstamp; int /*<<< orphan*/  is_mybeacon; scalar_t__ rs_more; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxbuf; struct sk_buff* frag; } ;
struct ath_softc {int ps_flags; TYPE_2__ rx; struct ath_hw* sc_ah; int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  dev; struct ieee80211_hw* hw; } ;
struct ath_rxbuf {int /*<<< orphan*/  list; int /*<<< orphan*/  bf_buf_addr; struct sk_buff* bf_mpdu; } ;
struct ath_rx_status {int rs_datalen; int flag; int /*<<< orphan*/  rs_tstamp; int /*<<< orphan*/  is_mybeacon; scalar_t__ rs_more; } ;
struct TYPE_3__ {int hw_caps; int rx_status_len; } ;
struct ath_hw {int imask; TYPE_1__ caps; } ;
struct ath_common {int /*<<< orphan*/  rx_bufsize; } ;
typedef  int /*<<< orphan*/  rs ;
typedef  enum ath9k_rx_qtype { ____Placeholder_ath9k_rx_qtype } ath9k_rx_qtype ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ATH9K_HW_CAP_EDMA ; 
 int ATH9K_INT_RXEOL ; 
 int ATH9K_INT_RXORN ; 
 int ATH9K_RX_QUEUE_HP ; 
 int ATH9K_RX_QUEUE_LP ; 
 int DMA_BIDIRECTIONAL ; 
 int DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int PS_WAIT_FOR_BEACON ; 
 int PS_WAIT_FOR_CAB ; 
 int PS_WAIT_FOR_PSPOLL_DATA ; 
 int RX_FLAG_MMIC_STRIPPED ; 
 int /*<<< orphan*/  RX_STAT_INC (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_antenna_check (struct ath_softc*,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  ath9k_apply_ampdu_details (struct ath_softc*,struct ieee80211_rx_status*,struct ieee80211_rx_status*) ; 
 scalar_t__ ath9k_check_auto_sleep (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_cmn_rx_skb_postprocess (struct ath_common*,struct sk_buff*,struct ieee80211_rx_status*,struct ieee80211_rx_status*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_gettsf64 (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_rxena (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_interrupts (struct ath_hw*) ; 
 int ath9k_rx_skb_preprocess (struct ath_softc*,struct sk_buff*,struct ieee80211_rx_status*,struct ieee80211_rx_status*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_debug_rate_stats (struct ath_softc*,struct ieee80211_rx_status*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath_dynack_sample_ack_ts (struct ath_hw*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct ath_rxbuf* ath_edma_get_next_rx_buf (struct ath_softc*,struct ieee80211_rx_status*,int) ; 
 struct ath_rxbuf* ath_get_next_rx_buf (struct ath_softc*,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  ath_rx_buf_relink (struct ath_softc*,struct ath_rxbuf*,int) ; 
 int /*<<< orphan*/  ath_rx_count_airtime (struct ath_softc*,struct ieee80211_rx_status*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath_rx_edma_buf_link (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath_rx_ps (struct ath_softc*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath_rxbuf_alloc (struct ath_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ieee80211_is_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_frags ; 
 int /*<<< orphan*/  rx_oom_err ; 
 int /*<<< orphan*/  rx_too_many_frags_err ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ath_rx_tasklet(struct ath_softc *sc, int flush, bool hp)
{
	struct ath_rxbuf *bf;
	struct sk_buff *skb = NULL, *requeue_skb, *hdr_skb;
	struct ieee80211_rx_status *rxs;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_hw *hw = sc->hw;
	int retval;
	struct ath_rx_status rs;
	enum ath9k_rx_qtype qtype;
	bool edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	int dma_type;
	u64 tsf = 0;
	unsigned long flags;
	dma_addr_t new_buf_addr;
	unsigned int budget = 512;
	struct ieee80211_hdr *hdr;

	if (edma)
		dma_type = DMA_BIDIRECTIONAL;
	else
		dma_type = DMA_FROM_DEVICE;

	qtype = hp ? ATH9K_RX_QUEUE_HP : ATH9K_RX_QUEUE_LP;

	tsf = ath9k_hw_gettsf64(ah);

	do {
		bool decrypt_error = false;

		memset(&rs, 0, sizeof(rs));
		if (edma)
			bf = ath_edma_get_next_rx_buf(sc, &rs, qtype);
		else
			bf = ath_get_next_rx_buf(sc, &rs);

		if (!bf)
			break;

		skb = bf->bf_mpdu;
		if (!skb)
			continue;

		/*
		 * Take frame header from the first fragment and RX status from
		 * the last one.
		 */
		if (sc->rx.frag)
			hdr_skb = sc->rx.frag;
		else
			hdr_skb = skb;

		rxs = IEEE80211_SKB_RXCB(hdr_skb);
		memset(rxs, 0, sizeof(struct ieee80211_rx_status));

		retval = ath9k_rx_skb_preprocess(sc, hdr_skb, &rs, rxs,
						 &decrypt_error, tsf);
		if (retval)
			goto requeue_drop_frag;

		/* Ensure we always have an skb to requeue once we are done
		 * processing the current buffer's skb */
		requeue_skb = ath_rxbuf_alloc(common, common->rx_bufsize, GFP_ATOMIC);

		/* If there is no memory we ignore the current RX'd frame,
		 * tell hardware it can give us a new frame using the old
		 * skb and put it at the tail of the sc->rx.rxbuf list for
		 * processing. */
		if (!requeue_skb) {
			RX_STAT_INC(sc, rx_oom_err);
			goto requeue_drop_frag;
		}

		/* We will now give hardware our shiny new allocated skb */
		new_buf_addr = dma_map_single(sc->dev, requeue_skb->data,
					      common->rx_bufsize, dma_type);
		if (unlikely(dma_mapping_error(sc->dev, new_buf_addr))) {
			dev_kfree_skb_any(requeue_skb);
			goto requeue_drop_frag;
		}

		/* Unmap the frame */
		dma_unmap_single(sc->dev, bf->bf_buf_addr,
				 common->rx_bufsize, dma_type);

		bf->bf_mpdu = requeue_skb;
		bf->bf_buf_addr = new_buf_addr;

		skb_put(skb, rs.rs_datalen + ah->caps.rx_status_len);
		if (ah->caps.rx_status_len)
			skb_pull(skb, ah->caps.rx_status_len);

		if (!rs.rs_more)
			ath9k_cmn_rx_skb_postprocess(common, hdr_skb, &rs,
						     rxs, decrypt_error);

		if (rs.rs_more) {
			RX_STAT_INC(sc, rx_frags);
			/*
			 * rs_more indicates chained descriptors which can be
			 * used to link buffers together for a sort of
			 * scatter-gather operation.
			 */
			if (sc->rx.frag) {
				/* too many fragments - cannot handle frame */
				dev_kfree_skb_any(sc->rx.frag);
				dev_kfree_skb_any(skb);
				RX_STAT_INC(sc, rx_too_many_frags_err);
				skb = NULL;
			}
			sc->rx.frag = skb;
			goto requeue;
		}

		if (sc->rx.frag) {
			int space = skb->len - skb_tailroom(hdr_skb);

			if (pskb_expand_head(hdr_skb, 0, space, GFP_ATOMIC) < 0) {
				dev_kfree_skb(skb);
				RX_STAT_INC(sc, rx_oom_err);
				goto requeue_drop_frag;
			}

			sc->rx.frag = NULL;

			skb_copy_from_linear_data(skb, skb_put(hdr_skb, skb->len),
						  skb->len);
			dev_kfree_skb_any(skb);
			skb = hdr_skb;
		}

		if (rxs->flag & RX_FLAG_MMIC_STRIPPED)
			skb_trim(skb, skb->len - 8);

		spin_lock_irqsave(&sc->sc_pm_lock, flags);
		if ((sc->ps_flags & (PS_WAIT_FOR_BEACON |
				     PS_WAIT_FOR_CAB |
				     PS_WAIT_FOR_PSPOLL_DATA)) ||
		    ath9k_check_auto_sleep(sc))
			ath_rx_ps(sc, skb, rs.is_mybeacon);
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

		ath9k_antenna_check(sc, &rs);
		ath9k_apply_ampdu_details(sc, &rs, rxs);
		ath_debug_rate_stats(sc, &rs, skb);
		ath_rx_count_airtime(sc, &rs, skb);

		hdr = (struct ieee80211_hdr *)skb->data;
		if (ieee80211_is_ack(hdr->frame_control))
			ath_dynack_sample_ack_ts(sc->sc_ah, skb, rs.rs_tstamp);

		ieee80211_rx(hw, skb);

requeue_drop_frag:
		if (sc->rx.frag) {
			dev_kfree_skb_any(sc->rx.frag);
			sc->rx.frag = NULL;
		}
requeue:
		list_add_tail(&bf->list, &sc->rx.rxbuf);

		if (!edma) {
			ath_rx_buf_relink(sc, bf, flush);
			if (!flush)
				ath9k_hw_rxena(ah);
		} else if (!flush) {
			ath_rx_edma_buf_link(sc, qtype);
		}

		if (!budget--)
			break;
	} while (1);

	if (!(ah->imask & ATH9K_INT_RXEOL)) {
		ah->imask |= (ATH9K_INT_RXEOL | ATH9K_INT_RXORN);
		ath9k_hw_set_interrupts(ah);
	}

	return 0;
}