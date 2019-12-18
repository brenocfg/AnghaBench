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
typedef  int /*<<< orphan*/  uint32_t ;
struct platform_device {int dummy; } ;
struct lpc32xx_nand_host {int /*<<< orphan*/  clk; int /*<<< orphan*/  io_base; int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  nand_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLCCFG_CE_LOW ; 
 int /*<<< orphan*/  SLC_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_wp_enable (struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct lpc32xx_nand_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_nand_remove(struct platform_device *pdev)
{
	uint32_t tmp;
	struct lpc32xx_nand_host *host = platform_get_drvdata(pdev);

	nand_release(&host->nand_chip);
	dma_release_channel(host->dma_chan);

	/* Force CE high */
	tmp = readl(SLC_CTRL(host->io_base));
	tmp &= ~SLCCFG_CE_LOW;
	writel(tmp, SLC_CTRL(host->io_base));

	clk_disable_unprepare(host->clk);
	lpc32xx_wp_enable(host);

	return 0;
}