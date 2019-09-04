#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct l2t_entry {int dummy; } ;
struct cpl_abort_rpl {int dummy; } ;
struct cpl_abort_req_rss {int status; } ;
struct chtls_sock {int /*<<< orphan*/  egress_dev; struct l2t_entry* l2t_entry; } ;
struct chtls_dev {TYPE_1__* lldi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int /*<<< orphan*/  GET_TID (struct cpl_abort_req_rss*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TCP_SYN_RECV ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 struct cpl_abort_req_rss* cplhdr (struct sk_buff*) ; 
 scalar_t__ csk_conn_inline (struct chtls_sock*) ; 
 int /*<<< orphan*/  cxgb4_l2t_send (int /*<<< orphan*/ ,struct sk_buff*,struct l2t_entry*) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  send_defer_abort_rpl (struct chtls_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  set_abort_rpl_wr (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void send_abort_rpl(struct sock *sk, struct sk_buff *skb,
			   struct chtls_dev *cdev, int status, int queue)
{
	struct cpl_abort_req_rss *req = cplhdr(skb);
	struct sk_buff *reply_skb;
	struct chtls_sock *csk;

	csk = rcu_dereference_sk_user_data(sk);

	reply_skb = alloc_skb(sizeof(struct cpl_abort_rpl),
			      GFP_KERNEL);

	if (!reply_skb) {
		req->status = (queue << 1);
		send_defer_abort_rpl(cdev, skb);
		return;
	}

	set_abort_rpl_wr(reply_skb, GET_TID(req), status);
	kfree_skb(skb);

	set_wr_txq(reply_skb, CPL_PRIORITY_DATA, queue);
	if (csk_conn_inline(csk)) {
		struct l2t_entry *e = csk->l2t_entry;

		if (e && sk->sk_state != TCP_SYN_RECV) {
			cxgb4_l2t_send(csk->egress_dev, reply_skb, e);
			return;
		}
	}
	cxgb4_ofld_send(cdev->lldi->ports[0], reply_skb);
}