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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  M88E1000_PHY_GEN_CONTROL ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

s32 e1000e_phy_reset_dsp(struct e1000_hw *hw)
{
	s32 ret_val;

	ret_val = e1e_wphy(hw, M88E1000_PHY_GEN_CONTROL, 0xC1);
	if (ret_val)
		return ret_val;

	return e1e_wphy(hw, M88E1000_PHY_GEN_CONTROL, 0);
}