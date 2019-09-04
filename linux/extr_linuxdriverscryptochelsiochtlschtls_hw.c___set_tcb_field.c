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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ulptx_idata {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cpl_set_tcb_field {int dummy; } ;
struct chtls_sock {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_CONTROL ; 
 int /*<<< orphan*/  __set_tcb_field_direct (struct chtls_sock*,struct cpl_set_tcb_field*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __skb_put (struct sk_buff*,unsigned int) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 unsigned int roundup (int,int) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_tcb_field(struct sock *sk, struct sk_buff *skb, u16 word,
			    u64 mask, u64 val, u8 cookie, int no_reply)
{
	struct cpl_set_tcb_field *req;
	struct chtls_sock *csk;
	struct ulptx_idata *sc;
	unsigned int wrlen;

	wrlen = roundup(sizeof(*req) + sizeof(*sc), 16);
	csk = rcu_dereference_sk_user_data(sk);

	req = (struct cpl_set_tcb_field *)__skb_put(skb, wrlen);
	__set_tcb_field_direct(csk, req, word, mask, val, cookie, no_reply);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, csk->port_id);
}