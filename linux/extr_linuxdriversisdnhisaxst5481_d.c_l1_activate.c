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
struct st5481_adapter {int /*<<< orphan*/  timer; } ;
struct FsmInst {struct st5481_adapter* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMER3 ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmRestartTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST5481_CMD_AR8 ; 
 int /*<<< orphan*/  ST5481_CMD_DR ; 
 int /*<<< orphan*/  ST5481_CMD_PUP ; 
 int /*<<< orphan*/  ST_L1_F4 ; 
 int /*<<< orphan*/  TIMER3_VALUE ; 
 int /*<<< orphan*/  st5481_ph_command (struct st5481_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
l1_activate(struct FsmInst *fi, int event, void *arg)
{
	struct st5481_adapter *adapter = fi->userdata;

	st5481_ph_command(adapter, ST5481_CMD_DR);
	st5481_ph_command(adapter, ST5481_CMD_PUP);
	FsmRestartTimer(&adapter->timer, TIMER3_VALUE, EV_TIMER3, NULL, 2);
	st5481_ph_command(adapter, ST5481_CMD_AR8);
	FsmChangeState(fi, ST_L1_F4);
}