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
struct cxgbi_sock {int /*<<< orphan*/  write_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cxgbi_sock_purge_write_queue(struct cxgbi_sock *csk)
{
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(&csk->write_queue)))
		__kfree_skb(skb);
}