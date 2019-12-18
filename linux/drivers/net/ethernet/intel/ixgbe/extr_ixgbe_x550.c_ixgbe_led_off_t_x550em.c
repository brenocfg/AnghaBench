#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_reg ) (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_PARAM ; 
 int /*<<< orphan*/  IXGBE_X557_LED_MANUAL_SET_MASK ; 
 scalar_t__ IXGBE_X557_LED_PROVISIONING ; 
 scalar_t__ IXGBE_X557_MAX_LED_INDEX ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_led_off_t_x550em(struct ixgbe_hw *hw, u32 led_idx)
{
	u16 phy_data;

	if (led_idx >= IXGBE_X557_MAX_LED_INDEX)
		return IXGBE_ERR_PARAM;

	/* To turn on the LED, set mode to ON. */
	hw->phy.ops.read_reg(hw, IXGBE_X557_LED_PROVISIONING + led_idx,
			     MDIO_MMD_VEND1, &phy_data);
	phy_data &= ~IXGBE_X557_LED_MANUAL_SET_MASK;
	hw->phy.ops.write_reg(hw, IXGBE_X557_LED_PROVISIONING + led_idx,
			      MDIO_MMD_VEND1, phy_data);

	return 0;
}