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
struct imxfb_info {int enabled; int map_dma; scalar_t__ regs; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_per; } ;

/* Variables and functions */
 int CPOS_CC0 ; 
 int CPOS_CC1 ; 
 scalar_t__ LCDC_CPOS ; 
 scalar_t__ LCDC_POS ; 
 scalar_t__ LCDC_RMCR ; 
 scalar_t__ LCDC_SSA ; 
 int RMCR_LCDC_EN_MX1 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imxfb_enable_controller(struct imxfb_info *fbi)
{
	int ret;

	if (fbi->enabled)
		return 0;

	pr_debug("Enabling LCD controller\n");

	writel(fbi->map_dma, fbi->regs + LCDC_SSA);

	/* panning offset 0 (0 pixel offset)        */
	writel(0x00000000, fbi->regs + LCDC_POS);

	/* disable hardware cursor */
	writel(readl(fbi->regs + LCDC_CPOS) & ~(CPOS_CC0 | CPOS_CC1),
		fbi->regs + LCDC_CPOS);

	/*
	 * RMCR_LCDC_EN_MX1 is present on i.MX1 only, but doesn't hurt
	 * on other SoCs
	 */
	writel(RMCR_LCDC_EN_MX1, fbi->regs + LCDC_RMCR);

	ret = clk_prepare_enable(fbi->clk_ipg);
	if (ret)
		goto err_enable_ipg;

	ret = clk_prepare_enable(fbi->clk_ahb);
	if (ret)
		goto err_enable_ahb;

	ret = clk_prepare_enable(fbi->clk_per);
	if (ret)
		goto err_enable_per;

	fbi->enabled = true;
	return 0;

err_enable_per:
	clk_disable_unprepare(fbi->clk_ahb);
err_enable_ahb:
	clk_disable_unprepare(fbi->clk_ipg);
err_enable_ipg:
	writel(0, fbi->regs + LCDC_RMCR);

	return ret;
}