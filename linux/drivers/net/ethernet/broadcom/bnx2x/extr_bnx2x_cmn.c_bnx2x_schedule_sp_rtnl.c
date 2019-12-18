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
typedef  int u32 ;
struct bnx2x {int /*<<< orphan*/  sp_rtnl_task; int /*<<< orphan*/  sp_rtnl_state; } ;
typedef  enum sp_rtnl_flag { ____Placeholder_sp_rtnl_flag } sp_rtnl_flag ;

/* Variables and functions */
 int BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int,char*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

void bnx2x_schedule_sp_rtnl(struct bnx2x *bp, enum sp_rtnl_flag flag,
			    u32 verbose)
{
	smp_mb__before_atomic();
	set_bit(flag, &bp->sp_rtnl_state);
	smp_mb__after_atomic();
	DP((BNX2X_MSG_SP | verbose), "Scheduling sp_rtnl task [Flag: %d]\n",
	   flag);
	schedule_delayed_work(&bp->sp_rtnl_task, 0);
}