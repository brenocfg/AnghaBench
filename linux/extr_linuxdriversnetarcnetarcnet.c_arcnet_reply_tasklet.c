#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ee_info; int /*<<< orphan*/  ee_data; int /*<<< orphan*/  ee_origin; int /*<<< orphan*/  ee_errno; } ;
struct sock_exterr_skb {TYPE_1__ ee; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; struct sock* sk; } ;
struct TYPE_5__ {struct sk_buff* skb; } ;
struct arcnet_local {int /*<<< orphan*/  dev; TYPE_2__ outgoing; int /*<<< orphan*/  reply_status; } ;
struct TYPE_6__ {int /*<<< orphan*/  tskey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMSG ; 
 struct sock_exterr_skb* SKB_EXT_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SO_EE_ORIGIN_TXSTATUS ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  memset (struct sock_exterr_skb*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_clone_sk (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int sock_queue_err_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static void arcnet_reply_tasklet(unsigned long data)
{
	struct arcnet_local *lp = (struct arcnet_local *)data;

	struct sk_buff *ackskb, *skb;
	struct sock_exterr_skb *serr;
	struct sock *sk;
	int ret;

	local_irq_disable();
	skb = lp->outgoing.skb;
	if (!skb || !skb->sk) {
		local_irq_enable();
		return;
	}

	sock_hold(skb->sk);
	sk = skb->sk;
	ackskb = skb_clone_sk(skb);
	sock_put(skb->sk);

	if (!ackskb) {
		local_irq_enable();
		return;
	}

	serr = SKB_EXT_ERR(ackskb);
	memset(serr, 0, sizeof(*serr));
	serr->ee.ee_errno = ENOMSG;
	serr->ee.ee_origin = SO_EE_ORIGIN_TXSTATUS;
	serr->ee.ee_data = skb_shinfo(skb)->tskey;
	serr->ee.ee_info = lp->reply_status;

	/* finally erasing outgoing skb */
	dev_kfree_skb(lp->outgoing.skb);
	lp->outgoing.skb = NULL;

	ackskb->dev = lp->dev;

	ret = sock_queue_err_skb(sk, ackskb);
	if (ret)
		kfree_skb(ackskb);

	local_irq_enable();
}