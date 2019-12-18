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
struct TYPE_2__ {int /*<<< orphan*/ * destructor_arg; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 scalar_t__ NET_IP_ALIGN ; 
 scalar_t__ NET_SKB_PAD ; 
 int __GFP_NOWARN ; 
 struct sk_buff* alloc_skb (scalar_t__,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sk_buff *xenvif_alloc_skb(unsigned int size)
{
	struct sk_buff *skb =
		alloc_skb(size + NET_SKB_PAD + NET_IP_ALIGN,
			  GFP_ATOMIC | __GFP_NOWARN);
	if (unlikely(skb == NULL))
		return NULL;

	/* Packets passed to netif_rx() must have some headroom. */
	skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);

	/* Initialize it here to avoid later surprises */
	skb_shinfo(skb)->destructor_arg = NULL;

	return skb;
}