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
struct layer2 {scalar_t__ tm; int /*<<< orphan*/  ui_queue; int /*<<< orphan*/  i_queue; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDL_STATUS_DOWN_IND ; 
 int /*<<< orphan*/  ST_L2_4 ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  freewin (struct layer2*) ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st5_dl_release_l2l3 (struct layer2*) ; 
 int /*<<< orphan*/  stop_t200 (struct layer2*,int) ; 

__attribute__((used)) static void
l2_st5_persistent_da(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;
	struct sk_buff *skb = arg;

	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	freewin(l2);
	stop_t200(l2, 19);
	st5_dl_release_l2l3(l2);
	mISDN_FsmChangeState(fi, ST_L2_4);
	if (l2->tm)
		l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	dev_kfree_skb(skb);
}