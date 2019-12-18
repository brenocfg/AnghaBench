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
typedef  scalar_t__ u_int ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  peer; int /*<<< orphan*/  (* recv ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;
struct manager {scalar_t__ lastid; int /*<<< orphan*/  options; TYPE_1__ ch; int /*<<< orphan*/  sendq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGR_PH_ACTIVE ; 
 int /*<<< orphan*/  MGR_PH_NOTREADY ; 
 scalar_t__ MISDN_ID_NONE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ mISDN_HEAD_ID (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_ack(struct manager *mgr, u_int id)
{
	if (test_bit(MGR_PH_NOTREADY, &mgr->options)) {
		if (id == mgr->lastid) {
			if (test_bit(MGR_PH_ACTIVE, &mgr->options)) {
				struct sk_buff	*skb;

				skb = skb_dequeue(&mgr->sendq);
				if (skb) {
					mgr->lastid = mISDN_HEAD_ID(skb);
					if (!mgr->ch.recv(mgr->ch.peer, skb))
						return;
					dev_kfree_skb(skb);
				}
			}
			mgr->lastid = MISDN_ID_NONE;
			test_and_clear_bit(MGR_PH_NOTREADY, &mgr->options);
		}
	}
}