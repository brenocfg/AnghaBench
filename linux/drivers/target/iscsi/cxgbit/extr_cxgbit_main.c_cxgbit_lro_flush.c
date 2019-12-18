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
struct t4_lro_mgr {int /*<<< orphan*/  lro_session_cnt; int /*<<< orphan*/  lro_pkts; int /*<<< orphan*/  lroq; } ;
struct sk_buff {int dummy; } ;
struct cxgbit_sock {int /*<<< orphan*/ * lro_skb; } ;
struct cxgbit_lro_cb {struct cxgbit_sock* csk; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgbit_put_csk (struct cxgbit_sock*) ; 
 int /*<<< orphan*/  cxgbit_queue_lro_skb (struct cxgbit_sock*,struct sk_buff*) ; 
 struct cxgbit_lro_cb* cxgbit_skb_lro_cb (struct sk_buff*) ; 

__attribute__((used)) static void cxgbit_lro_flush(struct t4_lro_mgr *lro_mgr, struct sk_buff *skb)
{
	struct cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	struct cxgbit_sock *csk = lro_cb->csk;

	csk->lro_skb = NULL;

	__skb_unlink(skb, &lro_mgr->lroq);
	cxgbit_queue_lro_skb(csk, skb);

	cxgbit_put_csk(csk);

	lro_mgr->lro_pkts++;
	lro_mgr->lro_session_cnt--;
}