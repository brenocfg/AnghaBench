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
struct layer2 {scalar_t__ tm; int /*<<< orphan*/  i_queue; int /*<<< orphan*/  t203; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_RELEASE_IND ; 
 int /*<<< orphan*/  MDL_STATUS_DOWN_IND ; 
 int /*<<< orphan*/  RSP ; 
 int /*<<< orphan*/  ST_L2_4 ; 
 int UA ; 
 int /*<<< orphan*/  freewin (struct layer2*) ; 
 int get_PollFlag (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_dl_release_l2l3 (struct layer2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_uframe (struct layer2*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_t200 (struct layer2*,int) ; 

__attribute__((used)) static void
l2_stop_multi(struct FsmInst *fi, int event, void *arg)
{
	struct layer2	*l2 = fi->userdata;
	struct sk_buff	*skb = arg;

	mISDN_FsmChangeState(fi, ST_L2_4);
	mISDN_FsmDelTimer(&l2->t203, 3);
	stop_t200(l2, 4);

	send_uframe(l2, skb, UA | get_PollFlag(l2, skb), RSP);
	skb_queue_purge(&l2->i_queue);
	freewin(l2);
	lapb_dl_release_l2l3(l2, DL_RELEASE_IND);
	if (l2->tm)
		l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
}