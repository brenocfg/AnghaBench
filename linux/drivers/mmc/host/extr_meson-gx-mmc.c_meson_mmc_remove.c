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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct meson_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  mmc_clk; int /*<<< orphan*/  bounce_dma_addr; int /*<<< orphan*/  bounce_buf; int /*<<< orphan*/  bounce_buf_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  dram_access_quirk; int /*<<< orphan*/  descs_dma_addr; int /*<<< orphan*/  descs; int /*<<< orphan*/  irq; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EMMC_DESC_BUF_LEN ; 
 scalar_t__ SD_EMMC_IRQ_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct meson_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct meson_host*) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_mmc_remove(struct platform_device *pdev)
{
	struct meson_host *host = dev_get_drvdata(&pdev->dev);

	mmc_remove_host(host->mmc);

	/* disable interrupts */
	writel(0, host->regs + SD_EMMC_IRQ_EN);
	free_irq(host->irq, host);

	dma_free_coherent(host->dev, SD_EMMC_DESC_BUF_LEN,
			  host->descs, host->descs_dma_addr);

	if (!host->dram_access_quirk)
		dma_free_coherent(host->dev, host->bounce_buf_size,
				  host->bounce_buf, host->bounce_dma_addr);

	clk_disable_unprepare(host->mmc_clk);
	clk_disable_unprepare(host->core_clk);

	mmc_free_host(host->mmc);
	return 0;
}