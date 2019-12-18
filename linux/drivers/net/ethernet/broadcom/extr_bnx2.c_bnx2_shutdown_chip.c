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
struct bnx2 {int flags; scalar_t__ wol; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_DRV_MSG_CODE_SUSPEND_NO_WOL ; 
 int /*<<< orphan*/  BNX2_DRV_MSG_CODE_SUSPEND_WOL ; 
 int /*<<< orphan*/  BNX2_DRV_MSG_CODE_UNLOAD_LNK_DN ; 
 int BNX2_FLAG_NO_WOL ; 
 int bnx2_reset_chip (struct bnx2*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_shutdown_chip(struct bnx2 *bp)
{
	u32 reset_code;

	if (bp->flags & BNX2_FLAG_NO_WOL)
		reset_code = BNX2_DRV_MSG_CODE_UNLOAD_LNK_DN;
	else if (bp->wol)
		reset_code = BNX2_DRV_MSG_CODE_SUSPEND_WOL;
	else
		reset_code = BNX2_DRV_MSG_CODE_SUSPEND_NO_WOL;

	return bnx2_reset_chip(bp, reset_code);
}