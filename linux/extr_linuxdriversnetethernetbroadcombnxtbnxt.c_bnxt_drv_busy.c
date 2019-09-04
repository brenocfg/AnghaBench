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
 int /*<<< orphan*/  BNXT_STATE_READ_STATS ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bnxt_drv_busy(struct bnxt *bp)
{
	return (test_bit(BNXT_STATE_IN_SP_TASK, &bp->state) ||
		test_bit(BNXT_STATE_READ_STATS, &bp->state));
}