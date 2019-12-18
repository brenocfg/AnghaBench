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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ppp {int mru; int /*<<< orphan*/  rstate; int /*<<< orphan*/  rc_state; TYPE_1__* rcomp; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int compress_proto; int (* decompress ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int) ;int /*<<< orphan*/  (* incomp ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
#define  CI_MPPE 128 
 int DECOMP_FATALERROR ; 
 int PPP_COMP ; 
 int PPP_HDRLEN ; 
 int PPP_PROTO (struct sk_buff*) ; 
 int /*<<< orphan*/  SC_DC_ERROR ; 
 int /*<<< orphan*/  SC_DC_FERROR ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ppp_receive_error (struct ppp*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *
ppp_decompress_frame(struct ppp *ppp, struct sk_buff *skb)
{
	int proto = PPP_PROTO(skb);
	struct sk_buff *ns;
	int len;

	/* Until we fix all the decompressor's need to make sure
	 * data portion is linear.
	 */
	if (!pskb_may_pull(skb, skb->len))
		goto err;

	if (proto == PPP_COMP) {
		int obuff_size;

		switch(ppp->rcomp->compress_proto) {
		case CI_MPPE:
			obuff_size = ppp->mru + PPP_HDRLEN + 1;
			break;
		default:
			obuff_size = ppp->mru + PPP_HDRLEN;
			break;
		}

		ns = dev_alloc_skb(obuff_size);
		if (!ns) {
			netdev_err(ppp->dev, "ppp_decompress_frame: "
				   "no memory\n");
			goto err;
		}
		/* the decompressor still expects the A/C bytes in the hdr */
		len = ppp->rcomp->decompress(ppp->rc_state, skb->data - 2,
				skb->len + 2, ns->data, obuff_size);
		if (len < 0) {
			/* Pass the compressed frame to pppd as an
			   error indication. */
			if (len == DECOMP_FATALERROR)
				ppp->rstate |= SC_DC_FERROR;
			kfree_skb(ns);
			goto err;
		}

		consume_skb(skb);
		skb = ns;
		skb_put(skb, len);
		skb_pull(skb, 2);	/* pull off the A/C bytes */

		/* Don't call __ppp_decompress_proto() here, but instead rely on
		 * corresponding algo (mppe/bsd/deflate) to decompress it.
		 */
	} else {
		/* Uncompressed frame - pass to decompressor so it
		   can update its dictionary if necessary. */
		if (ppp->rcomp->incomp)
			ppp->rcomp->incomp(ppp->rc_state, skb->data - 2,
					   skb->len + 2);
	}

	return skb;

 err:
	ppp->rstate |= SC_DC_ERROR;
	ppp_receive_error(ppp);
	return skb;
}