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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  cb; } ;
struct cfspi {int slave_talked; TYPE_2__* ndev; int /*<<< orphan*/  chead; scalar_t__ slave; } ;
struct caif_payload_info {scalar_t__ hdr_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int PAD_POW2 (scalar_t__,int) ; 
 int /*<<< orphan*/  caif_assert (scalar_t__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int spi_up_head_align ; 
 int spi_up_tail_align ; 

int cfspi_xmitfrm(struct cfspi *cfspi, u8 *buf, size_t len)
{
	u8 *dst = buf;
	caif_assert(buf);

	if (cfspi->slave && !cfspi->slave_talked)
		cfspi->slave_talked = true;

	do {
		struct sk_buff *skb;
		struct caif_payload_info *info;
		int spad = 0;
		int epad;

		skb = skb_dequeue(&cfspi->chead);
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
		if (spi_up_head_align > 1) {
			spad = 1 + PAD_POW2((info->hdr_len + 1), spi_up_head_align);
			*dst = (u8)(spad - 1);
			dst += spad;
		}

		/* Copy in CAIF frame. */
		skb_copy_bits(skb, 0, dst, skb->len);
		dst += skb->len;
		cfspi->ndev->stats.tx_packets++;
		cfspi->ndev->stats.tx_bytes += skb->len;

		/*
		 * Compute tail offset i.e. number of bytes to add to
		 * get the complete CAIF frame aligned.
		 */
		epad = PAD_POW2((skb->len + spad), spi_up_tail_align);
		dst += epad;

		dev_kfree_skb(skb);

	} while ((dst - buf) < len);

	return dst - buf;
}