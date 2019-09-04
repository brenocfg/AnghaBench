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
typedef  int /*<<< orphan*/  u_int ;
struct layer2 {char tei; int /*<<< orphan*/  ui_queue; int /*<<< orphan*/  flag; int /*<<< orphan*/  sapi; int /*<<< orphan*/  ch; } ;
struct FsmInst {scalar_t__ state; struct layer2* userdata; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  DL_INFORMATION_IND ; 
 int /*<<< orphan*/  DL_INFO_L2_CONNECT ; 
 int /*<<< orphan*/  FLG_L3_INIT ; 
 scalar_t__ ST_L2_3 ; 
 int /*<<< orphan*/  ST_L2_4 ; 
 int /*<<< orphan*/  establishlink (struct FsmInst*) ; 
 int /*<<< orphan*/  l2up_create (struct layer2*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_channel_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_ui (struct layer2*) ; 

__attribute__((used)) static void
l2_got_tei(struct FsmInst *fi, int event, void *arg)
{
	struct layer2	*l2 = fi->userdata;
	u_int		info;

	l2->tei = (signed char)(long)arg;
	set_channel_address(&l2->ch, l2->sapi, l2->tei);
	info = DL_INFO_L2_CONNECT;
	l2up_create(l2, DL_INFORMATION_IND, sizeof(info), &info);
	if (fi->state == ST_L2_3) {
		establishlink(fi);
		test_and_set_bit(FLG_L3_INIT, &l2->flag);
	} else
		mISDN_FsmChangeState(fi, ST_L2_4);
	if (skb_queue_len(&l2->ui_queue))
		tx_ui(l2);
}