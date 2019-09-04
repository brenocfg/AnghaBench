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
 int /*<<< orphan*/  BNXT_STATE_IN_SP_TASK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 

__attribute__((used)) static void bnxt_rtnl_lock_sp(struct bnxt *bp)
{
	/* We are called from bnxt_sp_task which has BNXT_STATE_IN_SP_TASK
	 * set.  If the device is being closed, bnxt_close() may be holding
	 * rtnl() and waiting for BNXT_STATE_IN_SP_TASK to clear.  So we
	 * must clear BNXT_STATE_IN_SP_TASK before holding rtnl().
	 */
	clear_bit(BNXT_STATE_IN_SP_TASK, &bp->state);
	rtnl_lock();
}