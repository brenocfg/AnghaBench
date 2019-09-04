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
struct TYPE_2__ {int tei; int /*<<< orphan*/  ui_queue; int /*<<< orphan*/  i_queue; } ;
struct PStack {TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_L2_1 ; 
 int /*<<< orphan*/  freewin (struct PStack*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st5_dl_release_l2l3 (struct PStack*) ; 
 int /*<<< orphan*/  stop_t200 (struct PStack*,int) ; 

__attribute__((used)) static void
l2_st5_tei_remove(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

	skb_queue_purge(&st->l2.i_queue);
	skb_queue_purge(&st->l2.ui_queue);
	freewin(st);
	st->l2.tei = -1;
	stop_t200(st, 17);
	st5_dl_release_l2l3(st);
	FsmChangeState(fi, ST_L2_1);
}