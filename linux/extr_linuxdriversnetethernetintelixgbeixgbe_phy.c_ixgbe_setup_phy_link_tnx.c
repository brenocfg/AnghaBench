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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {int autoneg_advertised; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_MII_1GBASE_T_ADVERTISE_XNP_TX ; 
 int IXGBE_MII_AUTONEG_REG ; 
 int /*<<< orphan*/  IXGBE_MII_AUTONEG_XNP_TX_REG ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_CTRL ; 
 int MDIO_AN_10GBT_CTRL_ADV10G ; 
 int /*<<< orphan*/  MDIO_AN_ADVERTISE ; 
 int MDIO_AN_CTRL1_RESTART ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 scalar_t__ ixgbe_check_reset_blocked (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_get_copper_link_capabilities_generic (struct ixgbe_hw*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

s32 ixgbe_setup_phy_link_tnx(struct ixgbe_hw *hw)
{
	u16 autoneg_reg = IXGBE_MII_AUTONEG_REG;
	bool autoneg = false;
	ixgbe_link_speed speed;

	ixgbe_get_copper_link_capabilities_generic(hw, &speed, &autoneg);

	if (speed & IXGBE_LINK_SPEED_10GB_FULL) {
		/* Set or unset auto-negotiation 10G advertisement */
		hw->phy.ops.read_reg(hw, MDIO_AN_10GBT_CTRL,
				     MDIO_MMD_AN,
				     &autoneg_reg);

		autoneg_reg &= ~MDIO_AN_10GBT_CTRL_ADV10G;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_10GB_FULL)
			autoneg_reg |= MDIO_AN_10GBT_CTRL_ADV10G;

		hw->phy.ops.write_reg(hw, MDIO_AN_10GBT_CTRL,
				      MDIO_MMD_AN,
				      autoneg_reg);
	}

	if (speed & IXGBE_LINK_SPEED_1GB_FULL) {
		/* Set or unset auto-negotiation 1G advertisement */
		hw->phy.ops.read_reg(hw, IXGBE_MII_AUTONEG_XNP_TX_REG,
				     MDIO_MMD_AN,
				     &autoneg_reg);

		autoneg_reg &= ~IXGBE_MII_1GBASE_T_ADVERTISE_XNP_TX;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_1GB_FULL)
			autoneg_reg |= IXGBE_MII_1GBASE_T_ADVERTISE_XNP_TX;

		hw->phy.ops.write_reg(hw, IXGBE_MII_AUTONEG_XNP_TX_REG,
				      MDIO_MMD_AN,
				      autoneg_reg);
	}

	if (speed & IXGBE_LINK_SPEED_100_FULL) {
		/* Set or unset auto-negotiation 100M advertisement */
		hw->phy.ops.read_reg(hw, MDIO_AN_ADVERTISE,
				     MDIO_MMD_AN,
				     &autoneg_reg);

		autoneg_reg &= ~(ADVERTISE_100FULL |
				 ADVERTISE_100HALF);
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_100_FULL)
			autoneg_reg |= ADVERTISE_100FULL;

		hw->phy.ops.write_reg(hw, MDIO_AN_ADVERTISE,
				      MDIO_MMD_AN,
				      autoneg_reg);
	}

	/* Blocked by MNG FW so don't reset PHY */
	if (ixgbe_check_reset_blocked(hw))
		return 0;

	/* Restart PHY autonegotiation and wait for completion */
	hw->phy.ops.read_reg(hw, MDIO_CTRL1,
			     MDIO_MMD_AN, &autoneg_reg);

	autoneg_reg |= MDIO_AN_CTRL1_RESTART;

	hw->phy.ops.write_reg(hw, MDIO_CTRL1,
			      MDIO_MMD_AN, autoneg_reg);
	return 0;
}