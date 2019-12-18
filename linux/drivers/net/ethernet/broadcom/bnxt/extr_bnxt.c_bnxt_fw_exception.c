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
struct bnxt {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_STATE_FW_FATAL_COND ; 
 int /*<<< orphan*/  bnxt_force_fw_reset (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_rtnl_lock_sp (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_rtnl_unlock_sp (struct bnxt*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bnxt_fw_exception(struct bnxt *bp)
{
	set_bit(BNXT_STATE_FW_FATAL_COND, &bp->state);
	bnxt_rtnl_lock_sp(bp);
	bnxt_force_fw_reset(bp);
	bnxt_rtnl_unlock_sp(bp);
}