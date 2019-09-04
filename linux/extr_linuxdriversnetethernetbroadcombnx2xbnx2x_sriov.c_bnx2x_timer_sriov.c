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
struct TYPE_2__ {int valid_bitmap; } ;
struct bnx2x {TYPE_1__ old_bulletin; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  BNX2X_SP_RTNL_VFPF_CHANNEL_DOWN ; 
 int CHANNEL_DOWN ; 
 int /*<<< orphan*/  bnx2x_sample_bulletin (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_schedule_sp_rtnl (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2x_timer_sriov(struct bnx2x *bp)
{
	bnx2x_sample_bulletin(bp);

	/* if channel is down we need to self destruct */
	if (bp->old_bulletin.valid_bitmap & 1 << CHANNEL_DOWN)
		bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_VFPF_CHANNEL_DOWN,
				       BNX2X_MSG_IOV);
}