#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct ppp {int dummy; } ;
struct channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ PPP_MP ; 
 scalar_t__ PPP_PROTO (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_receive_error (struct ppp*) ; 
 int /*<<< orphan*/  ppp_receive_mp_frame (struct ppp*,struct sk_buff*,struct channel*) ; 
 int /*<<< orphan*/  ppp_receive_nonmp_frame (struct ppp*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum_complete_unset (struct sk_buff*) ; 

__attribute__((used)) static void
ppp_receive_frame(struct ppp *ppp, struct sk_buff *skb, struct channel *pch)
{
	/* note: a 0-length skb is used as an error indication */
	if (skb->len > 0) {
		skb_checksum_complete_unset(skb);
#ifdef CONFIG_PPP_MULTILINK
		/* XXX do channel-level decompression here */
		if (PPP_PROTO(skb) == PPP_MP)
			ppp_receive_mp_frame(ppp, skb, pch);
		else
#endif /* CONFIG_PPP_MULTILINK */
			ppp_receive_nonmp_frame(ppp, skb);
	} else {
		kfree_skb(skb);
		ppp_receive_error(ppp);
	}
}