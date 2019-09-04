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
struct manager {int /*<<< orphan*/  datimer; } ;
struct FsmInst {scalar_t__ state; struct manager* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_L1_ACTIV ; 
 scalar_t__ ST_L1_DEACT_PENDING ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
da_activate(struct FsmInst *fi, int event, void *arg)
{
	struct manager	*mgr = fi->userdata;

	if (fi->state == ST_L1_DEACT_PENDING)
		mISDN_FsmDelTimer(&mgr->datimer, 1);
	mISDN_FsmChangeState(fi, ST_L1_ACTIV);
}