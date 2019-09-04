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
struct st5481_d_out {int /*<<< orphan*/  fsm; int /*<<< orphan*/  busy; } ;
struct st5481_adapter {struct st5481_d_out d_out; } ;
struct FsmInst {struct st5481_adapter* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_DOUT_WAIT_FOR_NOT_BUSY ; 
 int /*<<< orphan*/  dout_stop (struct FsmInst*,int,void*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dout_underrun(struct FsmInst *fsm, int event, void *arg)
{
	struct st5481_adapter *adapter = fsm->userdata;
	struct st5481_d_out *d_out = &adapter->d_out;

	if (test_bit(0, &d_out->busy) || test_bit(1, &d_out->busy)) {
		FsmChangeState(&d_out->fsm, ST_DOUT_WAIT_FOR_NOT_BUSY);
	}  else {
		dout_stop(fsm, event, arg);
	}
}