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
struct cxgbi_sock {int dummy; } ;

/* Variables and functions */
 struct sk_buff* cxgbi_sock_dequeue_wr (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

void cxgbi_sock_purge_wr_queue(struct cxgbi_sock *csk)
{
	struct sk_buff *skb;

	while ((skb = cxgbi_sock_dequeue_wr(csk)) != NULL)
		kfree_skb(skb);
}