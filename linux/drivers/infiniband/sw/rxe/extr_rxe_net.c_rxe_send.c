#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  sk; int /*<<< orphan*/  destructor; } ;
struct rxe_pkt_info {TYPE_3__* qp; } ;
struct TYPE_7__ {int /*<<< orphan*/  skb_out; TYPE_1__* sk; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int ip6_local_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int ip_local_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_xmit_eval (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  rxe_add_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  rxe_drop_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  rxe_skb_tx_dtor ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int rxe_send(struct rxe_pkt_info *pkt, struct sk_buff *skb)
{
	int err;

	skb->destructor = rxe_skb_tx_dtor;
	skb->sk = pkt->qp->sk->sk;

	rxe_add_ref(pkt->qp);
	atomic_inc(&pkt->qp->skb_out);

	if (skb->protocol == htons(ETH_P_IP)) {
		err = ip_local_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	} else if (skb->protocol == htons(ETH_P_IPV6)) {
		err = ip6_local_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	} else {
		pr_err("Unknown layer 3 protocol: %d\n", skb->protocol);
		atomic_dec(&pkt->qp->skb_out);
		rxe_drop_ref(pkt->qp);
		kfree_skb(skb);
		return -EINVAL;
	}

	if (unlikely(net_xmit_eval(err))) {
		pr_debug("error sending packet: %d\n", err);
		return -EAGAIN;
	}

	return 0;
}