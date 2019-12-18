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
struct layer2 {int /*<<< orphan*/  tei; int /*<<< orphan*/  ui_queue; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_TEI ; 
 int /*<<< orphan*/  ST_L2_1 ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_st24_tei_remove(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;

	skb_queue_purge(&l2->ui_queue);
	l2->tei = GROUP_TEI;
	mISDN_FsmChangeState(fi, ST_L2_1);
}