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
 int /*<<< orphan*/  BNXT_STATE_OPEN ; 
 int /*<<< orphan*/  bnxt_reset_task (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_rtnl_lock_sp (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_rtnl_unlock_sp (struct bnxt*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_reset(struct bnxt *bp, bool silent)
{
	bnxt_rtnl_lock_sp(bp);
	if (test_bit(BNXT_STATE_OPEN, &bp->state))
		bnxt_reset_task(bp, silent);
	bnxt_rtnl_unlock_sp(bp);
}