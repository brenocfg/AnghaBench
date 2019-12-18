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
struct tid_info {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ function; } ;
struct cxgbi_sock {int /*<<< orphan*/  lock; TYPE_1__ retry_timer; int /*<<< orphan*/  csk_family; int /*<<< orphan*/  port_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct cxgbi_device {int /*<<< orphan*/  owner; } ;
struct cxgb4_lld_info {struct tid_info* tids; } ;
struct cpl_act_open_rpl {int /*<<< orphan*/  atid_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOPEN_ATID_G (int /*<<< orphan*/ ) ; 
 unsigned int AOPEN_STATUS_G (int /*<<< orphan*/ ) ; 
 unsigned int CPL_ERR_ARP_MISS ; 
 unsigned int CPL_ERR_CONN_EXIST ; 
 unsigned int CPL_ERR_TCAM_FULL ; 
 unsigned int GET_TID (struct cpl_act_open_rpl*) ; 
 int HZ ; 
 unsigned int TID_TID_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  act_open_rpl_status_to_errno (unsigned int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ csk_act_open_retry_timer ; 
 int /*<<< orphan*/  cxgb4_remove_tid (struct tid_info*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgbi_sock_fail_act_open (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 scalar_t__ is_neg_adv (unsigned int) ; 
 scalar_t__ jiffies ; 
 struct cxgbi_sock* lookup_atid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_info_ipaddr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_act_open_rpl(struct cxgbi_device *cdev, struct sk_buff *skb)
{
	struct cxgbi_sock *csk;
	struct cpl_act_open_rpl *rpl = (struct cpl_act_open_rpl *)skb->data;
	unsigned int tid = GET_TID(rpl);
	unsigned int atid =
		TID_TID_G(AOPEN_ATID_G(be32_to_cpu(rpl->atid_status)));
	unsigned int status = AOPEN_STATUS_G(be32_to_cpu(rpl->atid_status));
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct tid_info *t = lldi->tids;

	csk = lookup_atid(t, atid);
	if (unlikely(!csk)) {
		pr_err("NO matching conn. atid %u, tid %u.\n", atid, tid);
		goto rel_skb;
	}

	pr_info_ipaddr("tid %u/%u, status %u.\n"
		       "csk 0x%p,%u,0x%lx. ", (&csk->saddr), (&csk->daddr),
		       atid, tid, status, csk, csk->state, csk->flags);

	if (is_neg_adv(status))
		goto rel_skb;

	module_put(cdev->owner);

	if (status && status != CPL_ERR_TCAM_FULL &&
	    status != CPL_ERR_CONN_EXIST &&
	    status != CPL_ERR_ARP_MISS)
		cxgb4_remove_tid(lldi->tids, csk->port_id, GET_TID(rpl),
				 csk->csk_family);

	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	if (status == CPL_ERR_CONN_EXIST &&
	    csk->retry_timer.function != csk_act_open_retry_timer) {
		csk->retry_timer.function = csk_act_open_retry_timer;
		mod_timer(&csk->retry_timer, jiffies + HZ / 2);
	} else
		cxgbi_sock_fail_act_open(csk,
					act_open_rpl_status_to_errno(status));

	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
rel_skb:
	__kfree_skb(skb);
}