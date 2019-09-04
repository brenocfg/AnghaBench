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
struct sock {int /*<<< orphan*/  sk_wmem_queued; } ;
struct sk_buff {scalar_t__ truesize; } ;
struct chtls_sock {int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 

__attribute__((used)) static void chtls_purge_write_queue(struct sock *sk)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(&csk->txq))) {
		sk->sk_wmem_queued -= skb->truesize;
		__kfree_skb(skb);
	}
}