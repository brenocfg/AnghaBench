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
struct sk_buff {int len; scalar_t__ data; } ;
struct ppp {int flags; TYPE_2__* dev; int /*<<< orphan*/  xc_state; TYPE_1__* xcomp; } ;
struct TYPE_4__ {int mtu; int hard_header_len; } ;
struct TYPE_3__ {int comp_extra; int (* compress ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PPP_HDRLEN ; 
 int SC_CCP_UP ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 

__attribute__((used)) static inline struct sk_buff *
pad_compress_skb(struct ppp *ppp, struct sk_buff *skb)
{
	struct sk_buff *new_skb;
	int len;
	int new_skb_size = ppp->dev->mtu +
		ppp->xcomp->comp_extra + ppp->dev->hard_header_len;
	int compressor_skb_size = ppp->dev->mtu +
		ppp->xcomp->comp_extra + PPP_HDRLEN;
	new_skb = alloc_skb(new_skb_size, GFP_ATOMIC);
	if (!new_skb) {
		if (net_ratelimit())
			netdev_err(ppp->dev, "PPP: no memory (comp pkt)\n");
		return NULL;
	}
	if (ppp->dev->hard_header_len > PPP_HDRLEN)
		skb_reserve(new_skb,
			    ppp->dev->hard_header_len - PPP_HDRLEN);

	/* compressor still expects A/C bytes in hdr */
	len = ppp->xcomp->compress(ppp->xc_state, skb->data - 2,
				   new_skb->data, skb->len + 2,
				   compressor_skb_size);
	if (len > 0 && (ppp->flags & SC_CCP_UP)) {
		consume_skb(skb);
		skb = new_skb;
		skb_put(skb, len);
		skb_pull(skb, 2);	/* pull off A/C bytes */
	} else if (len == 0) {
		/* didn't compress, or CCP not up yet */
		consume_skb(new_skb);
		new_skb = skb;
	} else {
		/*
		 * (len < 0)
		 * MPPE requires that we do not send unencrypted
		 * frames.  The compressor will return -1 if we
		 * should drop the frame.  We cannot simply test
		 * the compress_proto because MPPE and MPPC share
		 * the same number.
		 */
		if (net_ratelimit())
			netdev_err(ppp->dev, "ppp: compressor dropped pkt\n");
		kfree_skb(skb);
		consume_skb(new_skb);
		new_skb = NULL;
	}
	return new_skb;
}