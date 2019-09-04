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
 int /*<<< orphan*/  BNX2X_PATH0_RST_IN_PROG_BIT ; 
 int /*<<< orphan*/  BNX2X_PATH1_RST_IN_PROG_BIT ; 
 int /*<<< orphan*/  BNX2X_RECOVERY_GLOB_REG ; 
 scalar_t__ BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_RECOVERY_REG ; 
 int /*<<< orphan*/  REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_acquire_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_release_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 

void bnx2x_set_reset_in_progress(struct bnx2x *bp)
{
	u32 val;
	u32 bit = BP_PATH(bp) ?
		BNX2X_PATH1_RST_IN_PROG_BIT : BNX2X_PATH0_RST_IN_PROG_BIT;
	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);

	/* Set the bit */
	val |= bit;
	REG_WR(bp, BNX2X_RECOVERY_GLOB_REG, val);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
}