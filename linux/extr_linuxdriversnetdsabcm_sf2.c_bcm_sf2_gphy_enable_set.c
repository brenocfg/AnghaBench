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
typedef  int u32 ;
struct dsa_switch {int dummy; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int CK25_DIS ; 
 int EXT_PWR_DOWN ; 
 int IDDQ_BIAS ; 
 int IDDQ_GLOBAL_PWR ; 
 int PHY_RESET ; 
 int /*<<< orphan*/  REG_LED_CNTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SPHY_CNTRL ; 
 int SPDLNK_SRC_SEL ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int reg_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bcm_sf2_gphy_enable_set(struct dsa_switch *ds, bool enable)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg;

	reg = reg_readl(priv, REG_SPHY_CNTRL);
	if (enable) {
		reg |= PHY_RESET;
		reg &= ~(EXT_PWR_DOWN | IDDQ_BIAS | IDDQ_GLOBAL_PWR | CK25_DIS);
		reg_writel(priv, reg, REG_SPHY_CNTRL);
		udelay(21);
		reg = reg_readl(priv, REG_SPHY_CNTRL);
		reg &= ~PHY_RESET;
	} else {
		reg |= EXT_PWR_DOWN | IDDQ_BIAS | PHY_RESET;
		reg_writel(priv, reg, REG_SPHY_CNTRL);
		mdelay(1);
		reg |= CK25_DIS;
	}
	reg_writel(priv, reg, REG_SPHY_CNTRL);

	/* Use PHY-driven LED signaling */
	if (!enable) {
		reg = reg_readl(priv, REG_LED_CNTRL(0));
		reg |= SPDLNK_SRC_SEL;
		reg_writel(priv, reg, REG_LED_CNTRL(0));
	}
}