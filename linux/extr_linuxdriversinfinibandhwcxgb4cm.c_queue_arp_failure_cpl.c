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
struct sk_buff {scalar_t__ cb; } ;
struct TYPE_3__ {int opcode; } ;
struct cpl_act_establish {TYPE_1__ ot; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct c4iw_ep {TYPE_2__ com; } ;

/* Variables and functions */
 struct cpl_act_establish* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  sched (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void queue_arp_failure_cpl(struct c4iw_ep *ep, struct sk_buff *skb,
				  int cpl)
{
	struct cpl_act_establish *rpl = cplhdr(skb);

	/* Set our special ARP_FAILURE opcode */
	rpl->ot.opcode = cpl;

	/*
	 * Save ep in the skb->cb area, after where sched() will save the dev
	 * ptr.
	 */
	*((struct c4iw_ep **)(skb->cb + 2 * sizeof(void *))) = ep;
	sched(ep->com.dev, skb);
}