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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct nfp_net {TYPE_1__ mbox_cmsg; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ __nfp_ccm_get_tag (struct sk_buff*) ; 
 struct sk_buff* __skb_peek (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_queue_next (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
nfp_ccm_mbox_find_req(struct nfp_net *nn, __be16 tag, struct sk_buff *last)
{
	struct sk_buff *skb;

	skb = __skb_peek(&nn->mbox_cmsg.queue);
	while (true) {
		if (__nfp_ccm_get_tag(skb) == tag)
			return skb;

		if (skb == last)
			return NULL;
		skb = skb_queue_next(&nn->mbox_cmsg.queue, skb);
	}
}