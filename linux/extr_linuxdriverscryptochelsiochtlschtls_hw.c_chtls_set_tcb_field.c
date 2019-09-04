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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ulptx_idata {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cpl_set_tcb_field {int dummy; } ;
struct chtls_sock {int txq_idx; unsigned int wr_credits; unsigned int wr_unacked; int /*<<< orphan*/  egress_dev; } ;

/* Variables and functions */
 int CPL_PRIORITY_DATA ; 
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __set_tcb_field (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  enqueue_wr (struct chtls_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 unsigned int roundup (int,int) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int) ; 

__attribute__((used)) static int chtls_set_tcb_field(struct sock *sk, u16 word, u64 mask, u64 val)
{
	struct cpl_set_tcb_field *req;
	unsigned int credits_needed;
	struct chtls_sock *csk;
	struct ulptx_idata *sc;
	struct sk_buff *skb;
	unsigned int wrlen;
	int ret;

	wrlen = roundup(sizeof(*req) + sizeof(*sc), 16);

	skb = alloc_skb(wrlen, GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	credits_needed = DIV_ROUND_UP(wrlen, 16);
	csk = rcu_dereference_sk_user_data(sk);

	__set_tcb_field(sk, skb, word, mask, val, 0, 1);
	skb_set_queue_mapping(skb, (csk->txq_idx << 1) | CPL_PRIORITY_DATA);
	csk->wr_credits -= credits_needed;
	csk->wr_unacked += credits_needed;
	enqueue_wr(csk, skb);
	ret = cxgb4_ofld_send(csk->egress_dev, skb);
	if (ret < 0)
		kfree_skb(skb);
	return ret < 0 ? ret : 0;
}