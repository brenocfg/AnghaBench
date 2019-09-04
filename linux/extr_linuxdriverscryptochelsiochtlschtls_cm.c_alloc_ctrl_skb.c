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
struct sk_buff {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  refcount_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_shared (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *alloc_ctrl_skb(struct sk_buff *skb, int len)
{
	if (likely(skb && !skb_shared(skb) && !skb_cloned(skb))) {
		__skb_trim(skb, 0);
		refcount_add(2, &skb->users);
	} else {
		skb = alloc_skb(len, GFP_KERNEL | __GFP_NOFAIL);
	}
	return skb;
}