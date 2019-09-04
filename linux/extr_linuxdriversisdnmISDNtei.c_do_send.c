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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  peer; scalar_t__ (* recv ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;
struct manager {int /*<<< orphan*/  lastid; int /*<<< orphan*/  options; TYPE_1__ ch; int /*<<< orphan*/  deact; int /*<<< orphan*/  sendq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_UI ; 
 int /*<<< orphan*/  MGR_PH_ACTIVE ; 
 int /*<<< orphan*/  MGR_PH_NOTREADY ; 
 int /*<<< orphan*/  MISDN_ID_NONE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mISDN_FsmEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_HEAD_ID (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_send(struct manager *mgr)
{
	if (!test_bit(MGR_PH_ACTIVE, &mgr->options))
		return;

	if (!test_and_set_bit(MGR_PH_NOTREADY, &mgr->options)) {
		struct sk_buff	*skb = skb_dequeue(&mgr->sendq);

		if (!skb) {
			test_and_clear_bit(MGR_PH_NOTREADY, &mgr->options);
			return;
		}
		mgr->lastid = mISDN_HEAD_ID(skb);
		mISDN_FsmEvent(&mgr->deact, EV_UI, NULL);
		if (mgr->ch.recv(mgr->ch.peer, skb)) {
			dev_kfree_skb(skb);
			test_and_clear_bit(MGR_PH_NOTREADY, &mgr->options);
			mgr->lastid = MISDN_ID_NONE;
		}
	}
}