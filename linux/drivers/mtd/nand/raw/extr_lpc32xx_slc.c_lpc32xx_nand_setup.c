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
typedef  scalar_t__ uint32_t ;
struct lpc32xx_nand_host {int /*<<< orphan*/  io_base; TYPE_1__* ncfg; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  rsetup; int /*<<< orphan*/  rhold; int /*<<< orphan*/  rwidth; int /*<<< orphan*/  rdr_clks; int /*<<< orphan*/  wsetup; int /*<<< orphan*/  whold; int /*<<< orphan*/  wwidth; int /*<<< orphan*/  wdr_clks; } ;

/* Variables and functions */
 scalar_t__ LPC32XX_DEF_BUS_RATE ; 
 scalar_t__ SLCCTRL_SW_RESET ; 
 scalar_t__ SLCSTAT_INT_RDY_EN ; 
 scalar_t__ SLCSTAT_INT_TC ; 
 scalar_t__ SLCTAC_RDR (int /*<<< orphan*/ ) ; 
 scalar_t__ SLCTAC_RHOLD (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SLCTAC_RSETUP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SLCTAC_RWIDTH (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SLCTAC_WDR (int /*<<< orphan*/ ) ; 
 scalar_t__ SLCTAC_WHOLD (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SLCTAC_WSETUP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SLCTAC_WWIDTH (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_ICR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_IEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_TAC (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_nand_setup(struct lpc32xx_nand_host *host)
{
	uint32_t clkrate, tmp;

	/* Reset SLC controller */
	writel(SLCCTRL_SW_RESET, SLC_CTRL(host->io_base));
	udelay(1000);

	/* Basic setup */
	writel(0, SLC_CFG(host->io_base));
	writel(0, SLC_IEN(host->io_base));
	writel((SLCSTAT_INT_TC | SLCSTAT_INT_RDY_EN),
		SLC_ICR(host->io_base));

	/* Get base clock for SLC block */
	clkrate = clk_get_rate(host->clk);
	if (clkrate == 0)
		clkrate = LPC32XX_DEF_BUS_RATE;

	/* Compute clock setup values */
	tmp = SLCTAC_WDR(host->ncfg->wdr_clks) |
		SLCTAC_WWIDTH(clkrate, host->ncfg->wwidth) |
		SLCTAC_WHOLD(clkrate, host->ncfg->whold) |
		SLCTAC_WSETUP(clkrate, host->ncfg->wsetup) |
		SLCTAC_RDR(host->ncfg->rdr_clks) |
		SLCTAC_RWIDTH(clkrate, host->ncfg->rwidth) |
		SLCTAC_RHOLD(clkrate, host->ncfg->rhold) |
		SLCTAC_RSETUP(clkrate, host->ncfg->rsetup);
	writel(tmp, SLC_TAC(host->io_base));
}