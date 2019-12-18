#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int len; int /*<<< orphan*/  protocol; TYPE_5__* dev; int /*<<< orphan*/  data; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_10__ {scalar_t__ qlen; } ;
struct TYPE_9__ {int /*<<< orphan*/  rwait; TYPE_3__ rq; } ;
struct TYPE_8__ {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct ppp {int rstate; int flags; int debug; scalar_t__* npmode; TYPE_5__* dev; int /*<<< orphan*/  ppp_net; void* last_recv; scalar_t__ active_filter; scalar_t__ pass_filter; TYPE_2__ file; TYPE_1__ stats64; int /*<<< orphan*/  vj; scalar_t__ rc_state; } ;
struct TYPE_11__ {int flags; } ;

/* Variables and functions */
 scalar_t__ BPF_PROG_RUN (scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ NPMODE_PASS ; 
#define  PPP_CCP 130 
 int PPP_IP ; 
 scalar_t__ PPP_MAX_RQLEN ; 
 int PPP_PROTO (struct sk_buff*) ; 
#define  PPP_VJC_COMP 129 
#define  PPP_VJC_UNCOMP 128 
 int SC_DC_ERROR ; 
 int SC_DC_FERROR ; 
 int SC_DECOMP_RUN ; 
 int SC_MUST_COMP ; 
 int SC_REJ_COMP_TCP ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_net (TYPE_5__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  netdev_printk (int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/ * npindex_to_ethertype ; 
 int /*<<< orphan*/  ppp_ccp_peek (struct ppp*,struct sk_buff*,int) ; 
 struct sk_buff* ppp_decompress_frame (struct ppp*,struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_receive_error (struct ppp*) ; 
 int proto_to_npindex (int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (TYPE_3__*) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (TYPE_3__*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_scrub_packet (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 scalar_t__ skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slhc_remember (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int slhc_uncompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ppp_receive_nonmp_frame(struct ppp *ppp, struct sk_buff *skb)
{
	struct sk_buff *ns;
	int proto, len, npi;

	/*
	 * Decompress the frame, if compressed.
	 * Note that some decompressors need to see uncompressed frames
	 * that come in as well as compressed frames.
	 */
	if (ppp->rc_state && (ppp->rstate & SC_DECOMP_RUN) &&
	    (ppp->rstate & (SC_DC_FERROR | SC_DC_ERROR)) == 0)
		skb = ppp_decompress_frame(ppp, skb);

	if (ppp->flags & SC_MUST_COMP && ppp->rstate & SC_DC_FERROR)
		goto err;

	/* At this point the "Protocol" field MUST be decompressed, either in
	 * ppp_input(), ppp_decompress_frame() or in ppp_receive_mp_frame().
	 */
	proto = PPP_PROTO(skb);
	switch (proto) {
	case PPP_VJC_COMP:
		/* decompress VJ compressed packets */
		if (!ppp->vj || (ppp->flags & SC_REJ_COMP_TCP))
			goto err;

		if (skb_tailroom(skb) < 124 || skb_cloned(skb)) {
			/* copy to a new sk_buff with more tailroom */
			ns = dev_alloc_skb(skb->len + 128);
			if (!ns) {
				netdev_err(ppp->dev, "PPP: no memory "
					   "(VJ decomp)\n");
				goto err;
			}
			skb_reserve(ns, 2);
			skb_copy_bits(skb, 0, skb_put(ns, skb->len), skb->len);
			consume_skb(skb);
			skb = ns;
		}
		else
			skb->ip_summed = CHECKSUM_NONE;

		len = slhc_uncompress(ppp->vj, skb->data + 2, skb->len - 2);
		if (len <= 0) {
			netdev_printk(KERN_DEBUG, ppp->dev,
				      "PPP: VJ decompression error\n");
			goto err;
		}
		len += 2;
		if (len > skb->len)
			skb_put(skb, len - skb->len);
		else if (len < skb->len)
			skb_trim(skb, len);
		proto = PPP_IP;
		break;

	case PPP_VJC_UNCOMP:
		if (!ppp->vj || (ppp->flags & SC_REJ_COMP_TCP))
			goto err;

		/* Until we fix the decompressor need to make sure
		 * data portion is linear.
		 */
		if (!pskb_may_pull(skb, skb->len))
			goto err;

		if (slhc_remember(ppp->vj, skb->data + 2, skb->len - 2) <= 0) {
			netdev_err(ppp->dev, "PPP: VJ uncompressed error\n");
			goto err;
		}
		proto = PPP_IP;
		break;

	case PPP_CCP:
		ppp_ccp_peek(ppp, skb, 1);
		break;
	}

	++ppp->stats64.rx_packets;
	ppp->stats64.rx_bytes += skb->len - 2;

	npi = proto_to_npindex(proto);
	if (npi < 0) {
		/* control or unknown frame - pass it to pppd */
		skb_queue_tail(&ppp->file.rq, skb);
		/* limit queue length by dropping old frames */
		while (ppp->file.rq.qlen > PPP_MAX_RQLEN &&
		       (skb = skb_dequeue(&ppp->file.rq)))
			kfree_skb(skb);
		/* wake up any process polling or blocking on read */
		wake_up_interruptible(&ppp->file.rwait);

	} else {
		/* network protocol frame - give it to the kernel */

#ifdef CONFIG_PPP_FILTER
		/* check if the packet passes the pass and active filters */
		/* the filter instructions are constructed assuming
		   a four-byte PPP header on each packet */
		if (ppp->pass_filter || ppp->active_filter) {
			if (skb_unclone(skb, GFP_ATOMIC))
				goto err;

			*(u8 *)skb_push(skb, 2) = 0;
			if (ppp->pass_filter &&
			    BPF_PROG_RUN(ppp->pass_filter, skb) == 0) {
				if (ppp->debug & 1)
					netdev_printk(KERN_DEBUG, ppp->dev,
						      "PPP: inbound frame "
						      "not passed\n");
				kfree_skb(skb);
				return;
			}
			if (!(ppp->active_filter &&
			      BPF_PROG_RUN(ppp->active_filter, skb) == 0))
				ppp->last_recv = jiffies;
			__skb_pull(skb, 2);
		} else
#endif /* CONFIG_PPP_FILTER */
			ppp->last_recv = jiffies;

		if ((ppp->dev->flags & IFF_UP) == 0 ||
		    ppp->npmode[npi] != NPMODE_PASS) {
			kfree_skb(skb);
		} else {
			/* chop off protocol */
			skb_pull_rcsum(skb, 2);
			skb->dev = ppp->dev;
			skb->protocol = htons(npindex_to_ethertype[npi]);
			skb_reset_mac_header(skb);
			skb_scrub_packet(skb, !net_eq(ppp->ppp_net,
						      dev_net(ppp->dev)));
			netif_rx(skb);
		}
	}
	return;

 err:
	kfree_skb(skb);
	ppp_receive_error(ppp);
}