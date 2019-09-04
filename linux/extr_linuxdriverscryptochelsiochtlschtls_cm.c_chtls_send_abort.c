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
struct tcp_sock {int /*<<< orphan*/  snd_nxt; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cpl_abort_req {int rsvd1; int cmd; int /*<<< orphan*/  rsvd0; } ;
struct chtls_sock {int txq_idx; int /*<<< orphan*/  cdev; int /*<<< orphan*/  tid; int /*<<< orphan*/  txdata_skb_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_ABORT_REQ ; 
 int CPL_ABORT_SEND_RST ; 
 int CPL_PRIORITY_DATA ; 
 int /*<<< orphan*/  CSK_TX_DATA_SENT ; 
 int /*<<< orphan*/  INIT_TP_WR_CPL (struct cpl_abort_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort_arp_failure ; 
 struct sk_buff* alloc_ctrl_skb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csk_flag_nochk (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  send_or_defer (struct sock*,struct tcp_sock*,struct sk_buff*,int) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int) ; 
 int /*<<< orphan*/  t4_set_arp_err_handler (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void chtls_send_abort(struct sock *sk, int mode, struct sk_buff *skb)
{
	struct cpl_abort_req *req;
	struct chtls_sock *csk;
	struct tcp_sock *tp;

	csk = rcu_dereference_sk_user_data(sk);
	tp = tcp_sk(sk);

	if (!skb)
		skb = alloc_ctrl_skb(csk->txdata_skb_cache, sizeof(*req));

	req = (struct cpl_abort_req *)skb_put(skb, sizeof(*req));
	INIT_TP_WR_CPL(req, CPL_ABORT_REQ, csk->tid);
	skb_set_queue_mapping(skb, (csk->txq_idx << 1) | CPL_PRIORITY_DATA);
	req->rsvd0 = htonl(tp->snd_nxt);
	req->rsvd1 = !csk_flag_nochk(csk, CSK_TX_DATA_SENT);
	req->cmd = mode;
	t4_set_arp_err_handler(skb, csk->cdev, abort_arp_failure);
	send_or_defer(sk, tp, skb, mode == CPL_ABORT_SEND_RST);
}