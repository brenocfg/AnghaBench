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
struct hdmi_pll_8996 {int dummy; } ;
struct hdmi_phy {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HDMI_8996_PHY_CFG ; 
 int /*<<< orphan*/  hdmi_phy_write (struct hdmi_phy*,int /*<<< orphan*/ ,int) ; 
 struct hdmi_pll_8996* hw_clk_to_pll (struct clk_hw*) ; 
 struct hdmi_phy* pll_get_phy (struct hdmi_pll_8996*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hdmi_8996_pll_unprepare(struct clk_hw *hw)
{
	struct hdmi_pll_8996 *pll = hw_clk_to_pll(hw);
	struct hdmi_phy *phy = pll_get_phy(pll);

	hdmi_phy_write(phy, REG_HDMI_8996_PHY_CFG, 0x6);
	usleep_range(100, 150);
}