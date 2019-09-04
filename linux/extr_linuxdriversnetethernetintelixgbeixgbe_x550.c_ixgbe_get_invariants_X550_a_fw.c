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
struct TYPE_2__ {int /*<<< orphan*/ * set_phy_power; } ;
struct ixgbe_phy_info {TYPE_1__ ops; } ;
struct ixgbe_hw {struct ixgbe_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_get_invariants_X540 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_get_invariants_X550_a_fw(struct ixgbe_hw *hw)
{
	struct ixgbe_phy_info *phy = &hw->phy;

	/* Start with X540 invariants, since so similar */
	ixgbe_get_invariants_X540(hw);

	phy->ops.set_phy_power = NULL;

	return 0;
}