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
struct cdns_dphy_cfg {int pll_fbdiv; int /*<<< orphan*/  pll_opdiv; int /*<<< orphan*/  pll_ipdiv; } ;
struct cdns_dphy {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DPHY_CMN_FBDIV ; 
 int DPHY_CMN_FBDIV_FROM_REG ; 
 int DPHY_CMN_FBDIV_VAL (int,int) ; 
 int DPHY_CMN_IPDIV (int /*<<< orphan*/ ) ; 
 int DPHY_CMN_IPDIV_FROM_REG ; 
 int DPHY_CMN_OPDIV (int /*<<< orphan*/ ) ; 
 int DPHY_CMN_OPDIV_FROM_REG ; 
 scalar_t__ DPHY_CMN_OPIPDIV ; 
 scalar_t__ DPHY_CMN_PWM ; 
 int DPHY_CMN_PWM_DIV (int) ; 
 int DPHY_CMN_PWM_HIGH (int) ; 
 int DPHY_CMN_PWM_LOW (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_dphy_ref_set_pll_cfg(struct cdns_dphy *dphy,
				      const struct cdns_dphy_cfg *cfg)
{
	u32 fbdiv_low, fbdiv_high;

	fbdiv_low = (cfg->pll_fbdiv / 4) - 2;
	fbdiv_high = cfg->pll_fbdiv - fbdiv_low - 2;

	writel(DPHY_CMN_IPDIV_FROM_REG | DPHY_CMN_OPDIV_FROM_REG |
	       DPHY_CMN_IPDIV(cfg->pll_ipdiv) |
	       DPHY_CMN_OPDIV(cfg->pll_opdiv),
	       dphy->regs + DPHY_CMN_OPIPDIV);
	writel(DPHY_CMN_FBDIV_FROM_REG |
	       DPHY_CMN_FBDIV_VAL(fbdiv_low, fbdiv_high),
	       dphy->regs + DPHY_CMN_FBDIV);
	writel(DPHY_CMN_PWM_HIGH(6) | DPHY_CMN_PWM_LOW(0x101) |
	       DPHY_CMN_PWM_DIV(0x8),
	       dphy->regs + DPHY_CMN_PWM);
}