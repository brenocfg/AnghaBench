#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_5__ {scalar_t__ (* write_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IXGBE_MDIO_GLOBAL_ALARM_1_INT ; 
 int IXGBE_MDIO_GLOBAL_AN_VEN_ALM_INT_EN ; 
 int /*<<< orphan*/  IXGBE_MDIO_GLOBAL_INT_CHIP_STD_MASK ; 
 int /*<<< orphan*/  IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_MASK ; 
 int IXGBE_MDIO_GLOBAL_INT_DEV_FAULT_EN ; 
 int IXGBE_MDIO_GLOBAL_INT_HI_TEMP_EN ; 
 int /*<<< orphan*/  IXGBE_MDIO_GLOBAL_INT_MASK ; 
 int IXGBE_MDIO_GLOBAL_VEN_ALM_INT_EN ; 
 int IXGBE_MDIO_PMA_TX_VEN_LASI_INT_EN ; 
 int /*<<< orphan*/  IXGBE_MDIO_PMA_TX_VEN_LASI_INT_MASK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 scalar_t__ ixgbe_get_lasi_ext_t_x550em (struct ixgbe_hw*,int*) ; 
 scalar_t__ ixgbe_mac_x550em_a ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub8 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_enable_lasi_ext_t_x550em(struct ixgbe_hw *hw)
{
	u32 status;
	u16 reg;
	bool lsc;

	/* Clear interrupt flags */
	status = ixgbe_get_lasi_ext_t_x550em(hw, &lsc);

	/* Enable link status change alarm */

	/* Enable the LASI interrupts on X552 devices to receive notifications
	 * of the link configurations of the external PHY and correspondingly
	 * support the configuration of the internal iXFI link, since iXFI does
	 * not support auto-negotiation. This is not required for X553 devices
	 * having KR support, which performs auto-negotiations and which is used
	 * as the internal link to the external PHY. Hence adding a check here
	 * to avoid enabling LASI interrupts for X553 devices.
	 */
	if (hw->mac.type != ixgbe_mac_x550em_a) {
		status = hw->phy.ops.read_reg(hw,
					    IXGBE_MDIO_PMA_TX_VEN_LASI_INT_MASK,
					    MDIO_MMD_AN, &reg);
		if (status)
			return status;

		reg |= IXGBE_MDIO_PMA_TX_VEN_LASI_INT_EN;

		status = hw->phy.ops.write_reg(hw,
					    IXGBE_MDIO_PMA_TX_VEN_LASI_INT_MASK,
					    MDIO_MMD_AN, reg);
		if (status)
			return status;
	}

	/* Enable high temperature failure and global fault alarms */
	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_INT_MASK,
				      MDIO_MMD_VEND1,
				      &reg);
	if (status)
		return status;

	reg |= (IXGBE_MDIO_GLOBAL_INT_HI_TEMP_EN |
		IXGBE_MDIO_GLOBAL_INT_DEV_FAULT_EN);

	status = hw->phy.ops.write_reg(hw, IXGBE_MDIO_GLOBAL_INT_MASK,
				       MDIO_MMD_VEND1,
				       reg);
	if (status)
		return status;

	/* Enable vendor Auto-Neg alarm and Global Interrupt Mask 1 alarm */
	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_MASK,
				      MDIO_MMD_VEND1,
				      &reg);
	if (status)
		return status;

	reg |= (IXGBE_MDIO_GLOBAL_AN_VEN_ALM_INT_EN |
		IXGBE_MDIO_GLOBAL_ALARM_1_INT);

	status = hw->phy.ops.write_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_MASK,
				       MDIO_MMD_VEND1,
				       reg);
	if (status)
		return status;

	/* Enable chip-wide vendor alarm */
	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_STD_MASK,
				      MDIO_MMD_VEND1,
				      &reg);
	if (status)
		return status;

	reg |= IXGBE_MDIO_GLOBAL_VEN_ALM_INT_EN;

	status = hw->phy.ops.write_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_STD_MASK,
				       MDIO_MMD_VEND1,
				       reg);

	return status;
}