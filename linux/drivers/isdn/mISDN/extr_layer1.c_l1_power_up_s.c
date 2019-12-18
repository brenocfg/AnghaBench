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
struct layer1 {int /*<<< orphan*/  dch; int /*<<< orphan*/  (* dcb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  Flags; } ;
struct FsmInst {struct layer1* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L1_ACTIVATING ; 
 int /*<<< orphan*/  INFO3_P8 ; 
 int /*<<< orphan*/  ST_L1_F3 ; 
 int /*<<< orphan*/  ST_L1_F4 ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_power_up_s(struct FsmInst *fi, int event, void *arg)
{
	struct layer1 *l1 = fi->userdata;

	if (test_bit(FLG_L1_ACTIVATING, &l1->Flags)) {
		mISDN_FsmChangeState(fi, ST_L1_F4);
		l1->dcb(l1->dch, INFO3_P8);
	} else
		mISDN_FsmChangeState(fi, ST_L1_F3);
}