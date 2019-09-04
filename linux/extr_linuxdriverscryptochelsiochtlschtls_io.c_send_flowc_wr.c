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
struct fw_flowc_wr {int dummy; } ;
struct chtls_sock {int /*<<< orphan*/  txq_idx; int /*<<< orphan*/  egress_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_TX_DATA_SENT ; 
 int ENOMEM ; 
 int ULPCB_FLAG_NO_APPEND ; 
 int ULPCB_FLAG_NO_HDR ; 
 struct sk_buff* create_flowc_wr_skb (struct sock*,struct fw_flowc_wr*,int) ; 
 scalar_t__ csk_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int cxgb4_immdata_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fw_flowc_wr*,int) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  send_or_defer (struct sock*,struct tcp_sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_entail (struct sock*,struct sk_buff*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static int send_flowc_wr(struct sock *sk, struct fw_flowc_wr *flowc,
			 int flowclen)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *skb;
	int flowclen16;
	int ret;

	flowclen16 = flowclen / 16;

	if (csk_flag(sk, CSK_TX_DATA_SENT)) {
		skb = create_flowc_wr_skb(sk, flowc, flowclen);
		if (!skb)
			return -ENOMEM;

		skb_entail(sk, skb,
			   ULPCB_FLAG_NO_HDR | ULPCB_FLAG_NO_APPEND);
		return 0;
	}

	ret = cxgb4_immdata_send(csk->egress_dev,
				 csk->txq_idx,
				 flowc, flowclen);
	if (!ret)
		return flowclen16;
	skb = create_flowc_wr_skb(sk, flowc, flowclen);
	if (!skb)
		return -ENOMEM;
	send_or_defer(sk, tp, skb, 0);
	return flowclen16;
}