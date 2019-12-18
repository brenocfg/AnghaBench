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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  BP_ABS_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_VF_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HW_VF_HANDLE (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_pretend_func (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_enable_internal (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_vf_pglue_clear_err (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_semi_clear_err (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_func_en (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  storm_memset_vf_to_pf (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2x_vf_enable_access(struct bnx2x *bp, u8 abs_vfid)
{
	/* set the VF-PF association in the FW */
	storm_memset_vf_to_pf(bp, FW_VF_HANDLE(abs_vfid), BP_FUNC(bp));
	storm_memset_func_en(bp, FW_VF_HANDLE(abs_vfid), 1);

	/* clear vf errors*/
	bnx2x_vf_semi_clear_err(bp, abs_vfid);
	bnx2x_vf_pglue_clear_err(bp, abs_vfid);

	/* internal vf-enable - pretend */
	bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, abs_vfid));
	DP(BNX2X_MSG_IOV, "enabling internal access for vf %x\n", abs_vfid);
	bnx2x_vf_enable_internal(bp, true);
	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
}