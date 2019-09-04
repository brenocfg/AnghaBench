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
struct tcp_sock {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct chtls_sock {int /*<<< orphan*/  egress_dev; int /*<<< orphan*/  l2t_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_l2t_send (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 

__attribute__((used)) static inline void send_or_defer(struct sock *sk, struct tcp_sock *tp,
				 struct sk_buff *skb, int through_l2t)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	if (through_l2t) {
		/* send through L2T */
		cxgb4_l2t_send(csk->egress_dev, skb, csk->l2t_entry);
	} else {
		/* send directly */
		cxgb4_ofld_send(csk->egress_dev, skb);
	}
}