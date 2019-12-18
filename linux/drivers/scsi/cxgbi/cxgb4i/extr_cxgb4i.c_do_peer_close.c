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
struct tid_info {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct cxgbi_sock {int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct cxgbi_device {int dummy; } ;
struct cxgb4_lld_info {struct tid_info* tids; } ;
struct cpl_peer_close {int dummy; } ;

/* Variables and functions */
 unsigned int GET_TID (struct cpl_peer_close*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgbi_sock_rcv_peer_close (struct cxgbi_sock*) ; 
 struct cxgbi_sock* lookup_tid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_info_ipaddr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_peer_close(struct cxgbi_device *cdev, struct sk_buff *skb)
{
	struct cxgbi_sock *csk;
	struct cpl_peer_close *req = (struct cpl_peer_close *)skb->data;
	unsigned int tid = GET_TID(req);
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	if (unlikely(!csk)) {
		pr_err("can't find connection for tid %u.\n", tid);
		goto rel_skb;
	}
	pr_info_ipaddr("csk 0x%p,%u,0x%lx,%u.\n",
		       (&csk->saddr), (&csk->daddr),
		       csk, csk->state, csk->flags, csk->tid);
	cxgbi_sock_rcv_peer_close(csk);
rel_skb:
	__kfree_skb(skb);
}