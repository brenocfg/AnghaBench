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
typedef  int u8 ;
struct inno_hdmi_phy {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int RK3228_PRE_PLL_POWER_DOWN ; 
 int inno_read (struct inno_hdmi_phy*,int) ; 
 struct inno_hdmi_phy* to_inno_hdmi_phy (struct clk_hw*) ; 

__attribute__((used)) static int inno_hdmi_phy_rk3228_clk_is_prepared(struct clk_hw *hw)
{
	struct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	u8 status;

	status = inno_read(inno, 0xe0) & RK3228_PRE_PLL_POWER_DOWN;
	return status ? 0 : 1;
}