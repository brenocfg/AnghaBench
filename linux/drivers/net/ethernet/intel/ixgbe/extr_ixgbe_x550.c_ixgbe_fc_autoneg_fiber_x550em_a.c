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
struct TYPE_2__ {int fc_was_autonegged; int /*<<< orphan*/  requested_mode; int /*<<< orphan*/  current_mode; } ;
struct ixgbe_hw {TYPE_1__ fc; } ;

/* Variables and functions */

__attribute__((used)) static void ixgbe_fc_autoneg_fiber_x550em_a(struct ixgbe_hw *hw)
{
	hw->fc.fc_was_autonegged = false;
	hw->fc.current_mode = hw->fc.requested_mode;
}