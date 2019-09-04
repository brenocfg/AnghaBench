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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 size_t BP_FW_MB_IDX (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_MF_BD (struct bnx2x*) ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHMEM2_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_driver_state ; 

void bnx2x_set_os_driver_state(struct bnx2x *bp, u32 state)
{
	u32 cur;

	if (!IS_MF_BD(bp) || !SHMEM2_HAS(bp, os_driver_state) || IS_VF(bp))
		return;

	cur = SHMEM2_RD(bp, os_driver_state[BP_FW_MB_IDX(bp)]);
	DP(NETIF_MSG_IFUP, "Driver state %08x-->%08x\n",
	   cur, state);

	SHMEM2_WR(bp, os_driver_state[BP_FW_MB_IDX(bp)], state);
}