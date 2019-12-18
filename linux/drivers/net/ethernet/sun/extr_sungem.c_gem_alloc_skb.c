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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned long ALIGNED_RX_SKB_ADDR (int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned long) ; 

__attribute__((used)) static __inline__ struct sk_buff *gem_alloc_skb(struct net_device *dev, int size,
						gfp_t gfp_flags)
{
	struct sk_buff *skb = alloc_skb(size + 64, gfp_flags);

	if (likely(skb)) {
		unsigned long offset = ALIGNED_RX_SKB_ADDR(skb->data);
		skb_reserve(skb, offset);
	}
	return skb;
}