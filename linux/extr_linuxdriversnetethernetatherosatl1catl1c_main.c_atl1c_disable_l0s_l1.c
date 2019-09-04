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
typedef  int u16 ;
struct atl1c_hw {int ctrl_flags; } ;

/* Variables and functions */
 int ATL1C_ASPM_L0S_SUPPORT ; 
 int ATL1C_ASPM_L1_SUPPORT ; 
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  atl1c_set_aspm (struct atl1c_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1c_disable_l0s_l1(struct atl1c_hw *hw)
{
	u16 ctrl_flags = hw->ctrl_flags;

	hw->ctrl_flags &= ~(ATL1C_ASPM_L0S_SUPPORT | ATL1C_ASPM_L1_SUPPORT);
	atl1c_set_aspm(hw, SPEED_0);
	hw->ctrl_flags = ctrl_flags;
}