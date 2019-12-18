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
struct platform_device {int dummy; } ;
struct lpc32xx_nand_host {TYPE_1__* ncfg; int /*<<< orphan*/  clk; int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  irq; int /*<<< orphan*/  nand_chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  wp_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_wp_enable (struct lpc32xx_nand_host*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct lpc32xx_nand_host* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ use_dma ; 

__attribute__((used)) static int lpc32xx_nand_remove(struct platform_device *pdev)
{
	struct lpc32xx_nand_host *host = platform_get_drvdata(pdev);

	nand_release(&host->nand_chip);
	free_irq(host->irq, host);
	if (use_dma)
		dma_release_channel(host->dma_chan);

	clk_disable_unprepare(host->clk);
	clk_put(host->clk);

	lpc32xx_wp_enable(host);
	gpio_free(host->ncfg->wp_gpio);

	return 0;
}