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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ L2_HEADER_LEN ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static inline struct sk_buff *
_l2_alloc_skb(unsigned int len, gfp_t gfp_mask)
{
	struct sk_buff  *skb;

	skb = alloc_skb(len + L2_HEADER_LEN, gfp_mask);
	if (likely(skb))
		skb_reserve(skb, L2_HEADER_LEN);
	return skb;
}