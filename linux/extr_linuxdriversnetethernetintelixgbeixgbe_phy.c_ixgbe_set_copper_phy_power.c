#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {scalar_t__ (* write_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ phy; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_MDIO_PHY_SET_LOW_POWER_MODE ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 scalar_t__ ixgbe_check_reset_blocked (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_media_type_copper ; 
 scalar_t__ ixgbe_mng_present (struct ixgbe_hw*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 ixgbe_set_copper_phy_power(struct ixgbe_hw *hw, bool on)
{
	u32 status;
	u16 reg;

	/* Bail if we don't have copper phy */
	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_copper)
		return 0;

	if (!on && ixgbe_mng_present(hw))
		return 0;

	status = hw->phy.ops.read_reg(hw, MDIO_CTRL1, MDIO_MMD_VEND1, &reg);
	if (status)
		return status;

	if (on) {
		reg &= ~IXGBE_MDIO_PHY_SET_LOW_POWER_MODE;
	} else {
		if (ixgbe_check_reset_blocked(hw))
			return 0;
		reg |= IXGBE_MDIO_PHY_SET_LOW_POWER_MODE;
	}

	status = hw->phy.ops.write_reg(hw, MDIO_CTRL1, MDIO_MMD_VEND1, reg);
	return status;
}