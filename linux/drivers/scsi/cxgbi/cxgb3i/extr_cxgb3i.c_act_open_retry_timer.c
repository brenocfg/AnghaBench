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
struct timer_list {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {struct sock* sk; } ;
struct cxgbi_sock {int /*<<< orphan*/  lock; int /*<<< orphan*/  l2t; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
struct cpl_act_open_req {int dummy; } ;

/* Variables and functions */
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  act_open_arp_failure ; 
 struct sk_buff* alloc_wr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cxgbi_sock* csk ; 
 int /*<<< orphan*/  cxgbi_sock_fail_act_open (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 struct cxgbi_sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retry_timer ; 
 int /*<<< orphan*/  send_act_open_req (struct cxgbi_sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_arp_failure_handler (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void act_open_retry_timer(struct timer_list *t)
{
	struct cxgbi_sock *csk = from_timer(csk, t, retry_timer);
	struct sk_buff *skb;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);
	skb = alloc_wr(sizeof(struct cpl_act_open_req), 0, GFP_ATOMIC);
	if (!skb)
		cxgbi_sock_fail_act_open(csk, -ENOMEM);
	else {
		skb->sk = (struct sock *)csk;
		set_arp_failure_handler(skb, act_open_arp_failure);
		send_act_open_req(csk, skb, csk->l2t);
	}
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
}