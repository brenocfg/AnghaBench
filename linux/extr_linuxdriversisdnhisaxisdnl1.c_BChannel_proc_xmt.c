#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* l2l1 ) (struct PStack*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* l1l2 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  Flags; } ;
struct PStack {TYPE_2__ l2; TYPE_1__ l1; } ;
struct BCState {int /*<<< orphan*/  squeue; int /*<<< orphan*/  Flag; int /*<<< orphan*/  cs; struct PStack* st; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_ACTIV ; 
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int CONFIRM ; 
 int /*<<< orphan*/  FLG_L1_PULL_REQ ; 
 int PH_DEACTIVATE ; 
 int PH_PULL ; 
 int /*<<< orphan*/  debugl1 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
BChannel_proc_xmt(struct BCState *bcs)
{
	struct PStack *st = bcs->st;

	if (test_bit(BC_FLG_BUSY, &bcs->Flag)) {
		debugl1(bcs->cs, "BC_BUSY Error");
		return;
	}

	if (test_and_clear_bit(FLG_L1_PULL_REQ, &st->l1.Flags))
		st->l1.l1l2(st, PH_PULL | CONFIRM, NULL);
	if (!test_bit(BC_FLG_ACTIV, &bcs->Flag)) {
		if (!test_bit(BC_FLG_BUSY, &bcs->Flag) &&
		    skb_queue_empty(&bcs->squeue)) {
			st->l2.l2l1(st, PH_DEACTIVATE | CONFIRM, NULL);
		}
	}
}