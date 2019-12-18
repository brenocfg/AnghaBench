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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  force_speed_duplex; int /*<<< orphan*/  check_polarity; int /*<<< orphan*/  get_info; int /*<<< orphan*/  commit; void* write_reg; void* read_reg; int /*<<< orphan*/  write_reg_locked; int /*<<< orphan*/  read_reg_locked; int /*<<< orphan*/  power_down; int /*<<< orphan*/  power_up; } ;
struct e1000_phy_info {int addr; int reset_delay_us; int id; TYPE_1__ ops; void* autoneg_mask; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 void* AUTONEG_ADVERTISE_SPEED_DEFAULT ; 
#define  BME1000_E_PHY_ID 132 
 void* E1000_ALL_NOT_GIG ; 
 scalar_t__ E1000_ERR_PHY ; 
#define  IFE_C_E_PHY_ID 131 
#define  IFE_E_PHY_ID 130 
#define  IFE_PLUS_E_PHY_ID 129 
#define  IGP03E1000_E_PHY_ID 128 
 int /*<<< orphan*/  e1000_check_polarity_ife ; 
 int /*<<< orphan*/  e1000_check_polarity_igp ; 
 int /*<<< orphan*/  e1000_check_polarity_m88 ; 
 int /*<<< orphan*/  e1000_get_phy_info_ife ; 
 int /*<<< orphan*/  e1000_phy_bm ; 
 int /*<<< orphan*/  e1000_phy_force_speed_duplex_ife ; 
 int /*<<< orphan*/  e1000_phy_ife ; 
 int /*<<< orphan*/  e1000_phy_igp_3 ; 
 scalar_t__ e1000_phy_unknown ; 
 int /*<<< orphan*/  e1000_power_down_phy_copper_ich8lan ; 
 int /*<<< orphan*/  e1000_power_up_phy_copper ; 
 scalar_t__ e1000e_determine_phy_address (struct e1000_hw*) ; 
 scalar_t__ e1000e_get_phy_id (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_get_phy_info_igp ; 
 int /*<<< orphan*/  e1000e_get_phy_info_m88 ; 
 scalar_t__ e1000e_get_phy_type_from_id (int) ; 
 int /*<<< orphan*/  e1000e_phy_force_speed_duplex_igp ; 
 int /*<<< orphan*/  e1000e_phy_force_speed_duplex_m88 ; 
 int /*<<< orphan*/  e1000e_phy_sw_reset ; 
 void* e1000e_read_phy_reg_bm ; 
 int /*<<< orphan*/  e1000e_read_phy_reg_igp_locked ; 
 void* e1000e_write_phy_reg_bm ; 
 int /*<<< orphan*/  e1000e_write_phy_reg_igp_locked ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_init_phy_params_ich8lan(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 i = 0;

	phy->addr = 1;
	phy->reset_delay_us = 100;

	phy->ops.power_up = e1000_power_up_phy_copper;
	phy->ops.power_down = e1000_power_down_phy_copper_ich8lan;

	/* We may need to do this twice - once for IGP and if that fails,
	 * we'll set BM func pointers and try again
	 */
	ret_val = e1000e_determine_phy_address(hw);
	if (ret_val) {
		phy->ops.write_reg = e1000e_write_phy_reg_bm;
		phy->ops.read_reg = e1000e_read_phy_reg_bm;
		ret_val = e1000e_determine_phy_address(hw);
		if (ret_val) {
			e_dbg("Cannot determine PHY addr. Erroring out\n");
			return ret_val;
		}
	}

	phy->id = 0;
	while ((e1000_phy_unknown == e1000e_get_phy_type_from_id(phy->id)) &&
	       (i++ < 100)) {
		usleep_range(1000, 1100);
		ret_val = e1000e_get_phy_id(hw);
		if (ret_val)
			return ret_val;
	}

	/* Verify phy id */
	switch (phy->id) {
	case IGP03E1000_E_PHY_ID:
		phy->type = e1000_phy_igp_3;
		phy->autoneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;
		phy->ops.read_reg_locked = e1000e_read_phy_reg_igp_locked;
		phy->ops.write_reg_locked = e1000e_write_phy_reg_igp_locked;
		phy->ops.get_info = e1000e_get_phy_info_igp;
		phy->ops.check_polarity = e1000_check_polarity_igp;
		phy->ops.force_speed_duplex = e1000e_phy_force_speed_duplex_igp;
		break;
	case IFE_E_PHY_ID:
	case IFE_PLUS_E_PHY_ID:
	case IFE_C_E_PHY_ID:
		phy->type = e1000_phy_ife;
		phy->autoneg_mask = E1000_ALL_NOT_GIG;
		phy->ops.get_info = e1000_get_phy_info_ife;
		phy->ops.check_polarity = e1000_check_polarity_ife;
		phy->ops.force_speed_duplex = e1000_phy_force_speed_duplex_ife;
		break;
	case BME1000_E_PHY_ID:
		phy->type = e1000_phy_bm;
		phy->autoneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;
		phy->ops.read_reg = e1000e_read_phy_reg_bm;
		phy->ops.write_reg = e1000e_write_phy_reg_bm;
		phy->ops.commit = e1000e_phy_sw_reset;
		phy->ops.get_info = e1000e_get_phy_info_m88;
		phy->ops.check_polarity = e1000_check_polarity_m88;
		phy->ops.force_speed_duplex = e1000e_phy_force_speed_duplex_m88;
		break;
	default:
		return -E1000_ERR_PHY;
	}

	return 0;
}