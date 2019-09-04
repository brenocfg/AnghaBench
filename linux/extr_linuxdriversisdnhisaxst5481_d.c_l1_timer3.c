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
struct st5481_adapter {int dummy; } ;
struct FsmInst {struct st5481_adapter* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_L1L2 (struct st5481_adapter*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int INDICATION ; 
 int PH_DEACTIVATE ; 
 int /*<<< orphan*/  ST5481_CMD_DR ; 
 int /*<<< orphan*/  ST_L1_F3 ; 
 int /*<<< orphan*/  st5481_ph_command (struct st5481_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
l1_timer3(struct FsmInst *fi, int event, void *arg)
{
	struct st5481_adapter *adapter = fi->userdata;

	st5481_ph_command(adapter, ST5481_CMD_DR);
	FsmChangeState(fi, ST_L1_F3);
	D_L1L2(adapter, PH_DEACTIVATE | INDICATION, NULL);
}