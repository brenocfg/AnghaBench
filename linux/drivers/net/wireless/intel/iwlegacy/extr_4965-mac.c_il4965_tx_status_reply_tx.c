#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct il_priv {TYPE_4__* txq; } ;
struct il_ht_agg {int wait_for_ba; int frame_count; int start_idx; int bitmap; int /*<<< orphan*/  rate_n_flags; } ;
struct TYPE_5__ {struct agg_tx_status* agg_status; } ;
struct il4965_tx_resp {int frame_count; int /*<<< orphan*/  failure_frame; int /*<<< orphan*/  rate_n_flags; TYPE_1__ u; } ;
struct TYPE_7__ {TYPE_2__* rates; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; TYPE_3__ status; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; } ;
struct agg_tx_status {int /*<<< orphan*/  sequence; int /*<<< orphan*/  status; } ;
struct TYPE_8__ {struct sk_buff** skbs; } ;
struct TYPE_6__ {scalar_t__ count; } ;

/* Variables and functions */
 int AGG_TX_STATE_ABORT_MSK ; 
 int AGG_TX_STATE_FEW_BYTES_MSK ; 
 int /*<<< orphan*/  D_TX_REPLY (char*,...) ; 
 unsigned long long IEEE80211_SEQ_TO_SN (int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  IL_ERR (char*,int,unsigned long long,int /*<<< orphan*/ ) ; 
 int SEQ_TO_IDX (int) ; 
 int SEQ_TO_QUEUE (int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_hwrate_to_tx_control (struct il_priv*,int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  il4965_tx_status_to_mac80211 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
il4965_tx_status_reply_tx(struct il_priv *il, struct il_ht_agg *agg,
			  struct il4965_tx_resp *tx_resp, int txq_id,
			  u16 start_idx)
{
	u16 status;
	struct agg_tx_status *frame_status = tx_resp->u.agg_status;
	struct ieee80211_tx_info *info = NULL;
	struct ieee80211_hdr *hdr = NULL;
	u32 rate_n_flags = le32_to_cpu(tx_resp->rate_n_flags);
	int i, sh, idx;
	u16 seq;
	if (agg->wait_for_ba)
		D_TX_REPLY("got tx response w/o block-ack\n");

	agg->frame_count = tx_resp->frame_count;
	agg->start_idx = start_idx;
	agg->rate_n_flags = rate_n_flags;
	agg->bitmap = 0;

	/* num frames attempted by Tx command */
	if (agg->frame_count == 1) {
		/* Only one frame was attempted; no block-ack will arrive */
		status = le16_to_cpu(frame_status[0].status);
		idx = start_idx;

		D_TX_REPLY("FrameCnt = %d, StartIdx=%d idx=%d\n",
			   agg->frame_count, agg->start_idx, idx);

		info = IEEE80211_SKB_CB(il->txq[txq_id].skbs[idx]);
		info->status.rates[0].count = tx_resp->failure_frame + 1;
		info->flags &= ~IEEE80211_TX_CTL_AMPDU;
		info->flags |= il4965_tx_status_to_mac80211(status);
		il4965_hwrate_to_tx_control(il, rate_n_flags, info);

		D_TX_REPLY("1 Frame 0x%x failure :%d\n", status & 0xff,
			   tx_resp->failure_frame);
		D_TX_REPLY("Rate Info rate_n_flags=%x\n", rate_n_flags);

		agg->wait_for_ba = 0;
	} else {
		/* Two or more frames were attempted; expect block-ack */
		u64 bitmap = 0;
		int start = agg->start_idx;
		struct sk_buff *skb;

		/* Construct bit-map of pending frames within Tx win */
		for (i = 0; i < agg->frame_count; i++) {
			u16 sc;
			status = le16_to_cpu(frame_status[i].status);
			seq = le16_to_cpu(frame_status[i].sequence);
			idx = SEQ_TO_IDX(seq);
			txq_id = SEQ_TO_QUEUE(seq);

			if (status &
			    (AGG_TX_STATE_FEW_BYTES_MSK |
			     AGG_TX_STATE_ABORT_MSK))
				continue;

			D_TX_REPLY("FrameCnt = %d, txq_id=%d idx=%d\n",
				   agg->frame_count, txq_id, idx);

			skb = il->txq[txq_id].skbs[idx];
			if (WARN_ON_ONCE(skb == NULL))
				return -1;
			hdr = (struct ieee80211_hdr *) skb->data;

			sc = le16_to_cpu(hdr->seq_ctrl);
			if (idx != (IEEE80211_SEQ_TO_SN(sc) & 0xff)) {
				IL_ERR("BUG_ON idx doesn't match seq control"
				       " idx=%d, seq_idx=%d, seq=%d\n", idx,
				       IEEE80211_SEQ_TO_SN(sc), hdr->seq_ctrl);
				return -1;
			}

			D_TX_REPLY("AGG Frame i=%d idx %d seq=%d\n", i, idx,
				   IEEE80211_SEQ_TO_SN(sc));

			sh = idx - start;
			if (sh > 64) {
				sh = (start - idx) + 0xff;
				bitmap = bitmap << sh;
				sh = 0;
				start = idx;
			} else if (sh < -64)
				sh = 0xff - (start - idx);
			else if (sh < 0) {
				sh = start - idx;
				start = idx;
				bitmap = bitmap << sh;
				sh = 0;
			}
			bitmap |= 1ULL << sh;
			D_TX_REPLY("start=%d bitmap=0x%llx\n", start,
				   (unsigned long long)bitmap);
		}

		agg->bitmap = bitmap;
		agg->start_idx = start;
		D_TX_REPLY("Frames %d start_idx=%d bitmap=0x%llx\n",
			   agg->frame_count, agg->start_idx,
			   (unsigned long long)agg->bitmap);

		if (bitmap)
			agg->wait_for_ba = 1;
	}
	return 0;
}