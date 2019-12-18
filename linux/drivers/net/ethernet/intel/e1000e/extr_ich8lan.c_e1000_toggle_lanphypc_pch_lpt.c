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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_LPCD ; 
 int E1000_CTRL_LANPHYPC_OVERRIDE ; 
 int E1000_CTRL_LANPHYPC_VALUE ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK ; 
 int /*<<< orphan*/  FEXTNVM3 ; 
 scalar_t__ e1000_pch_lpt ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void e1000_toggle_lanphypc_pch_lpt(struct e1000_hw *hw)
{
	u32 mac_reg;

	/* Set Phy Config Counter to 50msec */
	mac_reg = er32(FEXTNVM3);
	mac_reg &= ~E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK;
	mac_reg |= E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC;
	ew32(FEXTNVM3, mac_reg);

	/* Toggle LANPHYPC Value bit */
	mac_reg = er32(CTRL);
	mac_reg |= E1000_CTRL_LANPHYPC_OVERRIDE;
	mac_reg &= ~E1000_CTRL_LANPHYPC_VALUE;
	ew32(CTRL, mac_reg);
	e1e_flush();
	usleep_range(10, 20);
	mac_reg &= ~E1000_CTRL_LANPHYPC_OVERRIDE;
	ew32(CTRL, mac_reg);
	e1e_flush();

	if (hw->mac.type < e1000_pch_lpt) {
		msleep(50);
	} else {
		u16 count = 20;

		do {
			usleep_range(5000, 6000);
		} while (!(er32(CTRL_EXT) & E1000_CTRL_EXT_LPCD) && count--);

		msleep(30);
	}
}