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
 unsigned int HDMI_8960_PHY_PLL_PWRDN_B_PD_PLL ; 
 unsigned int HDMI_8960_PHY_PLL_PWRDN_B_PLL_PWRDN_B ; 
 unsigned int HDMI_8960_PHY_PLL_STATUS0_PLL_LOCK ; 
 unsigned int HDMI_8960_PHY_REG12_PWRDN_B ; 
 unsigned int HDMI_8960_PHY_REG12_SW_RESET ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_PLL_LOCKDET_CFG0 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_PLL_LOCKDET_CFG1 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_PLL_PWRDN_B ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_PLL_STATUS0 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG12 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG2 ; 
 unsigned int hdmi_phy_read (struct hdmi_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_phy_write (struct hdmi_phy*,int /*<<< orphan*/ ,int) ; 
 struct hdmi_pll_8960* hw_clk_to_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  mb () ; 
 struct hdmi_phy* pll_get_phy (struct hdmi_pll_8960*) ; 
 unsigned int pll_read (struct hdmi_pll_8960*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_write (struct hdmi_pll_8960*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hdmi_pll_enable(struct clk_hw *hw)
{
	struct hdmi_pll_8960 *pll = hw_clk_to_pll(hw);
	struct hdmi_phy *phy = pll_get_phy(pll);
	int timeout_count, pll_lock_retry = 10;
	unsigned int val;

	DBG("");

	/* Assert PLL S/W reset */
	pll_write(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2, 0x8d);
	pll_write(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG0, 0x10);
	pll_write(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG1, 0x1a);

	/* Wait for a short time before de-asserting
	 * to allow the hardware to complete its job.
	 * This much of delay should be fine for hardware
	 * to assert and de-assert.
	 */
	udelay(10);

	/* De-assert PLL S/W reset */
	pll_write(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2, 0x0d);

	val = hdmi_phy_read(phy, REG_HDMI_8960_PHY_REG12);
	val |= HDMI_8960_PHY_REG12_SW_RESET;
	/* Assert PHY S/W reset */
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG12, val);
	val &= ~HDMI_8960_PHY_REG12_SW_RESET;
	/*
	 * Wait for a short time before de-asserting to allow the hardware to
	 * complete its job. This much of delay should be fine for hardware to
	 * assert and de-assert.
	 */
	udelay(10);
	/* De-assert PHY S/W reset */
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG12, val);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG2,  0x3f);

	val = hdmi_phy_read(phy, REG_HDMI_8960_PHY_REG12);
	val |= HDMI_8960_PHY_REG12_PWRDN_B;
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG12, val);
	/* Wait 10 us for enabling global power for PHY */
	mb();
	udelay(10);

	val = pll_read(pll, REG_HDMI_8960_PHY_PLL_PWRDN_B);
	val |= HDMI_8960_PHY_PLL_PWRDN_B_PLL_PWRDN_B;
	val &= ~HDMI_8960_PHY_PLL_PWRDN_B_PD_PLL;
	pll_write(pll, REG_HDMI_8960_PHY_PLL_PWRDN_B, val);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG2, 0x80);

	timeout_count = 1000;
	while (--pll_lock_retry > 0) {
		/* are we there yet? */
		val = pll_read(pll, REG_HDMI_8960_PHY_PLL_STATUS0);
		if (val & HDMI_8960_PHY_PLL_STATUS0_PLL_LOCK)
			break;

		udelay(1);

		if (--timeout_count > 0)
			continue;

		/*
		 * PLL has still not locked.
		 * Do a software reset and try again
		 * Assert PLL S/W reset first
		 */
		pll_write(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2, 0x8d);
		udelay(10);
		pll_write(pll, REG_HDMI_8960_PHY_PLL_LOCKDET_CFG2, 0x0d);

		/*
		 * Wait for a short duration for the PLL calibration
		 * before checking if the PLL gets locked
		 */
		udelay(350);

		timeout_count = 1000;
	}

	return 0;
}