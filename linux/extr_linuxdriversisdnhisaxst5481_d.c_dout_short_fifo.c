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
struct st5481_d_out {int /*<<< orphan*/  fsm; } ;
struct st5481_adapter {struct st5481_d_out d_out; } ;
struct FsmInst {struct st5481_adapter* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT_D_COUNTER ; 
 int /*<<< orphan*/  ST_DOUT_SHORT_WAIT_DEN ; 
 int /*<<< orphan*/  st5481_usb_device_ctrl_msg (struct st5481_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dout_short_fifo(struct FsmInst *fsm, int event, void *arg)
{
	struct st5481_adapter *adapter = fsm->userdata;
	struct st5481_d_out *d_out = &adapter->d_out;

	FsmChangeState(&d_out->fsm, ST_DOUT_SHORT_WAIT_DEN);
	st5481_usb_device_ctrl_msg(adapter, OUT_D_COUNTER, 16, NULL, NULL);
}