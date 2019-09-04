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
struct hdmi_pll_8960 {int dummy; } ;
struct hdmi_phy {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 unsigned int HDMI_8960_PHY_REG12_PWRDN_B ; 
 unsigned int HDMI_8960_PHY_REG12_SW_RESET ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_PLL_PWRDN_B ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG12 ; 
 unsigned int hdmi_phy_read (struct hdmi_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_phy_write (struct hdmi_phy*,int /*<<< orphan*/ ,unsigned int) ; 
 struct hdmi_pll_8960* hw_clk_to_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  mb () ; 
 struct hdmi_phy* pll_get_phy (struct hdmi_pll_8960*) ; 
 unsigned int pll_read (struct hdmi_pll_8960*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_write (struct hdmi_pll_8960*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hdmi_pll_disable(struct clk_hw *hw)
{
	struct hdmi_pll_8960 *pll = hw_clk_to_pll(hw);
	struct hdmi_phy *phy = pll_get_phy(pll);
	unsigned int val;

	DBG("");

	val = hdmi_phy_read(phy, REG_HDMI_8960_PHY_REG12);
	val &= ~HDMI_8960_PHY_REG12_PWRDN_B;
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG12, val);

	val = pll_read(pll, REG_HDMI_8960_PHY_PLL_PWRDN_B);
	val |= HDMI_8960_PHY_REG12_SW_RESET;
	val &= ~HDMI_8960_PHY_REG12_PWRDN_B;
	pll_write(pll, REG_HDMI_8960_PHY_PLL_PWRDN_B, val);
	/* Make sure HDMI PHY/PLL are powered down */
	mb();
}