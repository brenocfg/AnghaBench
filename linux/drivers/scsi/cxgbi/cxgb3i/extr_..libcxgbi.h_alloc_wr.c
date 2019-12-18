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
struct sk_buff {int /*<<< orphan*/  head; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

__attribute__((used)) static inline struct sk_buff *alloc_wr(int wrlen, int dlen, gfp_t gfp)
{
	struct sk_buff *skb = alloc_skb(wrlen + dlen, gfp);

	if (skb) {
		__skb_put(skb, wrlen);
		memset(skb->head, 0, wrlen + dlen);
	} else
		pr_info("alloc cpl wr skb %u+%u, OOM.\n", wrlen, dlen);
	return skb;
}