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
struct layer2 {scalar_t__ tm; int /*<<< orphan*/  flag; int /*<<< orphan*/  i_queue; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L3_INIT ; 
 int /*<<< orphan*/  FLG_LAPB ; 
 int /*<<< orphan*/  MDL_STATUS_DOWN_IND ; 
 int /*<<< orphan*/  PH_DEACTIVATE_REQ ; 
 int /*<<< orphan*/  ST_L2_4 ; 
 scalar_t__ get_PollFlagFree (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2_newid (struct layer2*) ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2down_create (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st5_dl_release_l2l3 (struct layer2*) ; 
 int /*<<< orphan*/  stop_t200 (struct layer2*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_st5_dm_release(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;
	struct sk_buff *skb = arg;

	if (get_PollFlagFree(l2, skb)) {
		stop_t200(l2, 7);
		if (!test_bit(FLG_L3_INIT, &l2->flag))
			skb_queue_purge(&l2->i_queue);
		if (test_bit(FLG_LAPB, &l2->flag))
			l2down_create(l2, PH_DEACTIVATE_REQ,
				      l2_newid(l2), 0, NULL);
		st5_dl_release_l2l3(l2);
		mISDN_FsmChangeState(fi, ST_L2_4);
		if (l2->tm)
			l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	}
}