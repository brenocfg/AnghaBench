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
struct sk_buff {int dummy; } ;
struct layer2 {scalar_t__ tm; int /*<<< orphan*/  T203; int /*<<< orphan*/  t203; scalar_t__ sow; scalar_t__ vr; scalar_t__ va; scalar_t__ vs; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_ESTABLISH_IND ; 
 int /*<<< orphan*/  EV_L2_T203 ; 
 int /*<<< orphan*/  MDL_STATUS_UP_IND ; 
 int /*<<< orphan*/  RSP ; 
 int /*<<< orphan*/  ST_L2_7 ; 
 int UA ; 
 int /*<<< orphan*/  clear_exception (struct layer2*) ; 
 int get_PollFlag (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2up (struct layer2*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  mISDN_FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_uframe (struct layer2*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
l2_start_multi(struct FsmInst *fi, int event, void *arg)
{
	struct layer2	*l2 = fi->userdata;
	struct sk_buff	*skb = arg;

	l2->vs = 0;
	l2->va = 0;
	l2->vr = 0;
	l2->sow = 0;
	clear_exception(l2);
	send_uframe(l2, NULL, UA | get_PollFlag(l2, skb), RSP);
	mISDN_FsmChangeState(fi, ST_L2_7);
	mISDN_FsmAddTimer(&l2->t203, l2->T203, EV_L2_T203, NULL, 3);
	skb_trim(skb, 0);
	l2up(l2, DL_ESTABLISH_IND, skb);
	if (l2->tm)
		l2_tei(l2, MDL_STATUS_UP_IND, 0);
}