#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  cb; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* flowctrl ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {scalar_t__ qlen; } ;
struct cfspi {scalar_t__ qd_low_mark; int /*<<< orphan*/  ndev; TYPE_1__ cfdev; scalar_t__ flow_off_sent; TYPE_2__ qhead; int /*<<< orphan*/  chead; } ;
struct caif_payload_info {scalar_t__ hdr_len; } ;

/* Variables and functions */
 scalar_t__ CAIF_MAX_SPI_FRAME ; 
 int CAIF_MAX_SPI_PKTS ; 
 int PAD_POW2 (scalar_t__,int) ; 
 struct sk_buff* skb_dequeue (TYPE_2__*) ; 
 struct sk_buff* skb_dequeue_tail (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int spi_up_head_align ; 
 int spi_up_tail_align ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

int cfspi_xmitlen(struct cfspi *cfspi)
{
	struct sk_buff *skb = NULL;
	int frm_len = 0;
	int pkts = 0;

	/*
	 * Decommit previously committed frames.
	 * skb_queue_splice_tail(&cfspi->chead,&cfspi->qhead)
	 */
	while (skb_peek(&cfspi->chead)) {
		skb = skb_dequeue_tail(&cfspi->chead);
		skb_queue_head(&cfspi->qhead, skb);
	}

	do {
		struct caif_payload_info *info = NULL;
		int spad = 0;
		int epad = 0;

		skb = skb_dequeue(&cfspi->qhead);
		if (!skb)
			break;

		/*
		 * Calculate length of frame including SPI padding.
		 * The payload position is found in the control buffer.
		 */
		info = (struct caif_payload_info *)&skb->cb;

		/*
		 * Compute head offset i.e. number of bytes to add to
		 * get the start of the payload aligned.
		 */
		if (spi_up_head_align > 1)
			spad = 1 + PAD_POW2((info->hdr_len + 1), spi_up_head_align);

		/*
		 * Compute tail offset i.e. number of bytes to add to
		 * get the complete CAIF frame aligned.
		 */
		epad = PAD_POW2((skb->len + spad), spi_up_tail_align);

		if ((skb->len + spad + epad + frm_len) <= CAIF_MAX_SPI_FRAME) {
			skb_queue_tail(&cfspi->chead, skb);
			pkts++;
			frm_len += skb->len + spad + epad;
		} else {
			/* Put back packet. */
			skb_queue_head(&cfspi->qhead, skb);
			break;
		}
	} while (pkts <= CAIF_MAX_SPI_PKTS);

	/*
	 * Send flow on if previously sent flow off
	 * and now go below the low water mark
	 */
	if (cfspi->flow_off_sent && cfspi->qhead.qlen < cfspi->qd_low_mark &&
		cfspi->cfdev.flowctrl) {
		cfspi->flow_off_sent = 0;
		cfspi->cfdev.flowctrl(cfspi->ndev, 1);
	}

	return frm_len;
}