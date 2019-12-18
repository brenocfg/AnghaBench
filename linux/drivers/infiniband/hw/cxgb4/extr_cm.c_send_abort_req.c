#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct cpl_abort_req {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; int /*<<< orphan*/  ep_skb_list; } ;
struct c4iw_ep {int /*<<< orphan*/  l2t; TYPE_2__ com; int /*<<< orphan*/  txq_idx; int /*<<< orphan*/  hwtid; } ;
struct TYPE_3__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  abort_arp_failure ; 
 int c4iw_l2t_send (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb_mk_abort_req (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (int,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_abort_req(struct c4iw_ep *ep)
{
	u32 wrlen = roundup(sizeof(struct cpl_abort_req), 16);
	struct sk_buff *req_skb = skb_dequeue(&ep->com.ep_skb_list);

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	if (WARN_ON(!req_skb))
		return -ENOMEM;

	cxgb_mk_abort_req(req_skb, wrlen, ep->hwtid, ep->txq_idx,
			  ep, abort_arp_failure);

	return c4iw_l2t_send(&ep->com.dev->rdev, req_skb, ep->l2t);
}