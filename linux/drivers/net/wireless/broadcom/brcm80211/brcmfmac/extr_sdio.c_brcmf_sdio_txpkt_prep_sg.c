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
typedef  int u16 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int len; int data_len; int end; int tail; scalar_t__ cb; scalar_t__ data; } ;
struct brcmf_sdio_dev {TYPE_1__* func2; } ;
struct brcmf_sdio {unsigned int sgentry_align; scalar_t__ head_align; struct brcmf_sdio_dev* sdiodev; } ;
struct TYPE_2__ {unsigned int cur_blksize; } ;

/* Variables and functions */
 int ALIGN_SKB_FLAG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_queue_after (struct sk_buff_head*,struct sk_buff*,struct sk_buff*) ; 
 int brcmf_sdio_txpkt_hdalign (struct brcmf_sdio*,struct sk_buff*) ; 
 struct sk_buff* brcmu_pkt_buf_get_skb (scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int skb_queue_is_last (struct sk_buff_head*,struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int brcmf_sdio_txpkt_prep_sg(struct brcmf_sdio *bus,
				    struct sk_buff_head *pktq,
				    struct sk_buff *pkt, u16 total_len)
{
	struct brcmf_sdio_dev *sdiodev;
	struct sk_buff *pkt_pad;
	u16 tail_pad, tail_chop, chain_pad;
	unsigned int blksize;
	bool lastfrm;
	int ntail, ret;

	sdiodev = bus->sdiodev;
	blksize = sdiodev->func2->cur_blksize;
	/* sg entry alignment should be a divisor of block size */
	WARN_ON(blksize % bus->sgentry_align);

	/* Check tail padding */
	lastfrm = skb_queue_is_last(pktq, pkt);
	tail_pad = 0;
	tail_chop = pkt->len % bus->sgentry_align;
	if (tail_chop)
		tail_pad = bus->sgentry_align - tail_chop;
	chain_pad = (total_len + tail_pad) % blksize;
	if (lastfrm && chain_pad)
		tail_pad += blksize - chain_pad;
	if (skb_tailroom(pkt) < tail_pad && pkt->len > blksize) {
		pkt_pad = brcmu_pkt_buf_get_skb(tail_pad + tail_chop +
						bus->head_align);
		if (pkt_pad == NULL)
			return -ENOMEM;
		ret = brcmf_sdio_txpkt_hdalign(bus, pkt_pad);
		if (unlikely(ret < 0)) {
			kfree_skb(pkt_pad);
			return ret;
		}
		memcpy(pkt_pad->data,
		       pkt->data + pkt->len - tail_chop,
		       tail_chop);
		*(u16 *)(pkt_pad->cb) = ALIGN_SKB_FLAG + tail_chop;
		skb_trim(pkt, pkt->len - tail_chop);
		skb_trim(pkt_pad, tail_pad + tail_chop);
		__skb_queue_after(pktq, pkt, pkt_pad);
	} else {
		ntail = pkt->data_len + tail_pad -
			(pkt->end - pkt->tail);
		if (skb_cloned(pkt) || ntail > 0)
			if (pskb_expand_head(pkt, 0, ntail, GFP_ATOMIC))
				return -ENOMEM;
		if (skb_linearize(pkt))
			return -ENOMEM;
		__skb_put(pkt, tail_pad);
	}

	return tail_pad;
}