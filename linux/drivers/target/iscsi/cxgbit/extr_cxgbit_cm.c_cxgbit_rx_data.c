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
struct sk_buff {int dummy; } ;
struct cxgbit_sock {int dummy; } ;
struct cxgb4_lld_info {struct tid_info* tids; } ;
struct cxgbit_device {struct cxgb4_lld_info lldi; } ;
struct cpl_rx_data {int dummy; } ;

/* Variables and functions */
 unsigned int GET_TID (struct cpl_rx_data*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct cpl_rx_data* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbit_queue_rx_skb (struct cxgbit_sock*,struct sk_buff*) ; 
 struct cxgbit_sock* lookup_tid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cxgbit_rx_data(struct cxgbit_device *cdev, struct sk_buff *skb)
{
	struct cxgbit_sock *csk;
	struct cpl_rx_data *cpl = cplhdr(skb);
	unsigned int tid = GET_TID(cpl);
	struct cxgb4_lld_info *lldi = &cdev->lldi;
	struct tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	if (unlikely(!csk)) {
		pr_err("can't find conn. for tid %u.\n", tid);
		goto rel_skb;
	}

	cxgbit_queue_rx_skb(csk, skb);
	return;
rel_skb:
	__kfree_skb(skb);
}