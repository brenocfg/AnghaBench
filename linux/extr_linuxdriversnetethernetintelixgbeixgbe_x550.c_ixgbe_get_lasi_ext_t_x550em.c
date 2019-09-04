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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_OVERTEMP ; 
 int /*<<< orphan*/  IXGBE_MDIO_AUTO_NEG_VENDOR_TX_ALARM2 ; 
 int IXGBE_MDIO_AUTO_NEG_VEN_LSC ; 
 int /*<<< orphan*/  IXGBE_MDIO_GLOBAL_ALARM_1 ; 
 int IXGBE_MDIO_GLOBAL_ALARM_1_INT ; 
 int IXGBE_MDIO_GLOBAL_ALM_1_DEV_FAULT ; 
 int IXGBE_MDIO_GLOBAL_ALM_1_HI_TMP_FAIL ; 
 int IXGBE_MDIO_GLOBAL_AN_VEN_ALM_INT_EN ; 
 int /*<<< orphan*/  IXGBE_MDIO_GLOBAL_CHIP_STD_INT_FLAG ; 
 int /*<<< orphan*/  IXGBE_MDIO_GLOBAL_FAULT_MSG ; 
 int IXGBE_MDIO_GLOBAL_FAULT_MSG_HI_TMP ; 
 int /*<<< orphan*/  IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_FLAG ; 
 int IXGBE_MDIO_GLOBAL_STD_ALM2_INT ; 
 int IXGBE_MDIO_GLOBAL_VEN_ALM_INT_EN ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int /*<<< orphan*/  ixgbe_set_copper_phy_power (struct ixgbe_hw*,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static s32 ixgbe_get_lasi_ext_t_x550em(struct ixgbe_hw *hw, bool *lsc)
{
	u32 status;
	u16 reg;

	*lsc = false;

	/* Vendor alarm triggered */
	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_CHIP_STD_INT_FLAG,
				      MDIO_MMD_VEND1,
				      &reg);

	if (status || !(reg & IXGBE_MDIO_GLOBAL_VEN_ALM_INT_EN))
		return status;

	/* Vendor Auto-Neg alarm triggered or Global alarm 1 triggered */
	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_FLAG,
				      MDIO_MMD_VEND1,
				      &reg);

	if (status || !(reg & (IXGBE_MDIO_GLOBAL_AN_VEN_ALM_INT_EN |
				IXGBE_MDIO_GLOBAL_ALARM_1_INT)))
		return status;

	/* Global alarm triggered */
	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_ALARM_1,
				      MDIO_MMD_VEND1,
				      &reg);

	if (status)
		return status;

	/* If high temperature failure, then return over temp error and exit */
	if (reg & IXGBE_MDIO_GLOBAL_ALM_1_HI_TMP_FAIL) {
		/* power down the PHY in case the PHY FW didn't already */
		ixgbe_set_copper_phy_power(hw, false);
		return IXGBE_ERR_OVERTEMP;
	}
	if (reg & IXGBE_MDIO_GLOBAL_ALM_1_DEV_FAULT) {
		/*  device fault alarm triggered */
		status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_FAULT_MSG,
					  MDIO_MMD_VEND1,
					  &reg);
		if (status)
			return status;

		/* if device fault was due to high temp alarm handle and exit */
		if (reg == IXGBE_MDIO_GLOBAL_FAULT_MSG_HI_TMP) {
			/* power down the PHY in case the PHY FW didn't */
			ixgbe_set_copper_phy_power(hw, false);
			return IXGBE_ERR_OVERTEMP;
		}
	}

	/* Vendor alarm 2 triggered */
	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_CHIP_STD_INT_FLAG,
				      MDIO_MMD_AN, &reg);

	if (status || !(reg & IXGBE_MDIO_GLOBAL_STD_ALM2_INT))
		return status;

	/* link connect/disconnect event occurred */
	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_AUTO_NEG_VENDOR_TX_ALARM2,
				      MDIO_MMD_AN, &reg);

	if (status)
		return status;

	/* Indicate LSC */
	if (reg & IXGBE_MDIO_AUTO_NEG_VEN_LSC)
		*lsc = true;

	return 0;
}