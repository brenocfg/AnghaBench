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
typedef  scalar_t__ u8 ;
struct sk_buff {int len; int /*<<< orphan*/  cb; } ;
struct cfhsi_desc {int* cffrm_len; int /*<<< orphan*/  header; scalar_t__ offset; scalar_t__* emb_frm; } ;
struct TYPE_4__ {int /*<<< orphan*/  tail_align; int /*<<< orphan*/  head_align; } ;
struct cfhsi {int /*<<< orphan*/  lock; TYPE_3__* ndev; TYPE_1__ cfg; } ;
struct caif_payload_info {int hdr_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 scalar_t__ CFHSI_DESC_SHORT_SZ ; 
 int CFHSI_DESC_SZ ; 
 int CFHSI_MAX_EMB_FRM_SZ ; 
 int CFHSI_MAX_PKTS ; 
 int /*<<< orphan*/  CFHSI_PIGGY_DESC ; 
 int PAD_POW2 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cfhsi_can_send_aggregate (struct cfhsi*) ; 
 struct sk_buff* cfhsi_dequeue (struct cfhsi*) ; 
 int /*<<< orphan*/  cfhsi_update_aggregation_stats (struct cfhsi*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cfhsi_tx_frm(struct cfhsi_desc *desc, struct cfhsi *cfhsi)
{
	int nfrms = 0;
	int pld_len = 0;
	struct sk_buff *skb;
	u8 *pfrm = desc->emb_frm + CFHSI_MAX_EMB_FRM_SZ;

	skb = cfhsi_dequeue(cfhsi);
	if (!skb)
		return 0;

	/* Clear offset. */
	desc->offset = 0;

	/* Check if we can embed a CAIF frame. */
	if (skb->len < CFHSI_MAX_EMB_FRM_SZ) {
		struct caif_payload_info *info;
		int hpad;
		int tpad;

		/* Calculate needed head alignment and tail alignment. */
		info = (struct caif_payload_info *)&skb->cb;

		hpad = 1 + PAD_POW2((info->hdr_len + 1), cfhsi->cfg.head_align);
		tpad = PAD_POW2((skb->len + hpad), cfhsi->cfg.tail_align);

		/* Check if frame still fits with added alignment. */
		if ((skb->len + hpad + tpad) <= CFHSI_MAX_EMB_FRM_SZ) {
			u8 *pemb = desc->emb_frm;
			desc->offset = CFHSI_DESC_SHORT_SZ;
			*pemb = (u8)(hpad - 1);
			pemb += hpad;

			/* Update network statistics. */
			spin_lock_bh(&cfhsi->lock);
			cfhsi->ndev->stats.tx_packets++;
			cfhsi->ndev->stats.tx_bytes += skb->len;
			cfhsi_update_aggregation_stats(cfhsi, skb, -1);
			spin_unlock_bh(&cfhsi->lock);

			/* Copy in embedded CAIF frame. */
			skb_copy_bits(skb, 0, pemb, skb->len);

			/* Consume the SKB */
			consume_skb(skb);
			skb = NULL;
		}
	}

	/* Create payload CAIF frames. */
	while (nfrms < CFHSI_MAX_PKTS) {
		struct caif_payload_info *info;
		int hpad;
		int tpad;

		if (!skb)
			skb = cfhsi_dequeue(cfhsi);

		if (!skb)
			break;

		/* Calculate needed head alignment and tail alignment. */
		info = (struct caif_payload_info *)&skb->cb;

		hpad = 1 + PAD_POW2((info->hdr_len + 1), cfhsi->cfg.head_align);
		tpad = PAD_POW2((skb->len + hpad), cfhsi->cfg.tail_align);

		/* Fill in CAIF frame length in descriptor. */
		desc->cffrm_len[nfrms] = hpad + skb->len + tpad;

		/* Fill head padding information. */
		*pfrm = (u8)(hpad - 1);
		pfrm += hpad;

		/* Update network statistics. */
		spin_lock_bh(&cfhsi->lock);
		cfhsi->ndev->stats.tx_packets++;
		cfhsi->ndev->stats.tx_bytes += skb->len;
		cfhsi_update_aggregation_stats(cfhsi, skb, -1);
		spin_unlock_bh(&cfhsi->lock);

		/* Copy in CAIF frame. */
		skb_copy_bits(skb, 0, pfrm, skb->len);

		/* Update payload length. */
		pld_len += desc->cffrm_len[nfrms];

		/* Update frame pointer. */
		pfrm += skb->len + tpad;

		/* Consume the SKB */
		consume_skb(skb);
		skb = NULL;

		/* Update number of frames. */
		nfrms++;
	}

	/* Unused length fields should be zero-filled (according to SPEC). */
	while (nfrms < CFHSI_MAX_PKTS) {
		desc->cffrm_len[nfrms] = 0x0000;
		nfrms++;
	}

	/* Check if we can piggy-back another descriptor. */
	if (cfhsi_can_send_aggregate(cfhsi))
		desc->header |= CFHSI_PIGGY_DESC;
	else
		desc->header &= ~CFHSI_PIGGY_DESC;

	return CFHSI_DESC_SZ + pld_len;
}