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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ DEFAULT_TIPG_IPGT_1000_80003ES2LAN ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_HD_CTRL_1000_DEFAULT ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_OFFSET_HD_CTRL ; 
 scalar_t__ E1000_TIPG_IPGT_MASK ; 
 int /*<<< orphan*/  GG82563_KMCR_PASS_FALSE_CARRIER ; 
 scalar_t__ GG82563_MAX_KMRN_RETRY ; 
 int /*<<< orphan*/  GG82563_PHY_KMRN_MODE_CTRL ; 
 int /*<<< orphan*/  TIPG ; 
 scalar_t__ e1000_write_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static s32 e1000_cfg_kmrn_1000_80003es2lan(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 reg_data, reg_data2;
	u32 tipg;
	u32 i = 0;

	reg_data = E1000_KMRNCTRLSTA_HD_CTRL_1000_DEFAULT;
	ret_val =
	    e1000_write_kmrn_reg_80003es2lan(hw,
					     E1000_KMRNCTRLSTA_OFFSET_HD_CTRL,
					     reg_data);
	if (ret_val)
		return ret_val;

	/* Configure Transmit Inter-Packet Gap */
	tipg = er32(TIPG);
	tipg &= ~E1000_TIPG_IPGT_MASK;
	tipg |= DEFAULT_TIPG_IPGT_1000_80003ES2LAN;
	ew32(TIPG, tipg);

	do {
		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL, &reg_data);
		if (ret_val)
			return ret_val;

		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL, &reg_data2);
		if (ret_val)
			return ret_val;
		i++;
	} while ((reg_data != reg_data2) && (i < GG82563_MAX_KMRN_RETRY));

	reg_data &= ~GG82563_KMCR_PASS_FALSE_CARRIER;

	return e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, reg_data);
}