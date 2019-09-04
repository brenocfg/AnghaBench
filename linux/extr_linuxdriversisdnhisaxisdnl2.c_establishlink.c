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
typedef  int u_char ;
struct TYPE_2__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  t203; scalar_t__ rc; } ;
struct PStack {TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  FLG_PEND_REL ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int SABM ; 
 int SABME ; 
 int /*<<< orphan*/  ST_L2_5 ; 
 int /*<<< orphan*/  clear_exception (TYPE_1__*) ; 
 int /*<<< orphan*/  freewin (struct PStack*) ; 
 int /*<<< orphan*/  restart_t200 (struct PStack*,int) ; 
 int /*<<< orphan*/  send_uframe (struct PStack*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
establishlink(struct FsmInst *fi)
{
	struct PStack *st = fi->userdata;
	u_char cmd;

	clear_exception(&st->l2);
	st->l2.rc = 0;
	cmd = (test_bit(FLG_MOD128, &st->l2.flag) ? SABME : SABM) | 0x10;
	send_uframe(st, cmd, CMD);
	FsmDelTimer(&st->l2.t203, 1);
	restart_t200(st, 1);
	test_and_clear_bit(FLG_PEND_REL, &st->l2.flag);
	freewin(st);
	FsmChangeState(fi, ST_L2_5);
}