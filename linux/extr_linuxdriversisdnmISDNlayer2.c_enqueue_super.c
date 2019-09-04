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
struct layer2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PH_DATA_REQ ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2_newid (struct layer2*) ; 
 scalar_t__ l2down (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static inline void
enqueue_super(struct layer2 *l2, struct sk_buff *skb)
{
	if (l2down(l2, PH_DATA_REQ, l2_newid(l2), skb))
		dev_kfree_skb(skb);
}