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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ (* write_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct ixgbe_mac_info {TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  lan_id; } ;
struct ixgbe_hw {TYPE_1__ bus; struct ixgbe_mac_info mac; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_LINK_SETUP ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20_AN37_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20_AN_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20_SGMII_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_10G ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_1G ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_MASK ; 
#define  IXGBE_LINK_SPEED_10GB_FULL 129 
#define  IXGBE_LINK_SPEED_1GB_FULL 128 
 int /*<<< orphan*/  IXGBE_SB_IOSF_TARGET_KR_PHY ; 
 scalar_t__ ixgbe_restart_an_internal_phy_x550em (struct ixgbe_hw*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_setup_sfi_x550a(struct ixgbe_hw *hw, ixgbe_link_speed *speed)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	s32 status;
	u32 reg_val;

	/* Disable all AN and force speed to 10G Serial. */
	status = mac->ops.read_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	if (status)
		return status;

	reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_AN_EN;
	reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_AN37_EN;
	reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SGMII_EN;
	reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_MASK;

	/* Select forced link speed for internal PHY. */
	switch (*speed) {
	case IXGBE_LINK_SPEED_10GB_FULL:
		reg_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_10G;
		break;
	case IXGBE_LINK_SPEED_1GB_FULL:
		reg_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_1G;
		break;
	default:
		/* Other link speeds are not supported by internal PHY. */
		return IXGBE_ERR_LINK_SETUP;
	}

	status = mac->ops.write_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);

	/* Toggle port SW reset by AN reset. */
	status = ixgbe_restart_an_internal_phy_x550em(hw);

	return status;
}