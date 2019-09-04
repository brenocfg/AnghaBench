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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_ABS_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  DORQ_REG_VF_USAGE_CNT ; 
 scalar_t__ FW_VF_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HW_VF_HANDLE (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_flr_clnup_poll_count (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_flr_clnup_poll_hw_counter (struct bnx2x*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_pretend_func (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_send_final_clnup (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_tx_hw_flushed (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_vf_flr_clnup_hw(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	u32 poll_cnt = bnx2x_flr_clnup_poll_count(bp);

	/* DQ usage counter */
	bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, vf->abs_vfid));
	bnx2x_flr_clnup_poll_hw_counter(bp, DORQ_REG_VF_USAGE_CNT,
					"DQ VF usage counter timed out",
					poll_cnt);
	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));

	/* FW cleanup command - poll for the results */
	if (bnx2x_send_final_clnup(bp, (u8)FW_VF_HANDLE(vf->abs_vfid),
				   poll_cnt))
		BNX2X_ERR("VF[%d] Final cleanup timed-out\n", vf->abs_vfid);

	/* verify TX hw is flushed */
	bnx2x_tx_hw_flushed(bp, poll_cnt);
}