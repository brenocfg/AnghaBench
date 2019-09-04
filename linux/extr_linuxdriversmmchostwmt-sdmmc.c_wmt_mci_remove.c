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
typedef  int u32 ;
struct wmt_mci_priv {int /*<<< orphan*/  clk_sdmmc; scalar_t__ sdmmc_base; int /*<<< orphan*/  irq_dma; int /*<<< orphan*/  irq_regular; int /*<<< orphan*/  dma_desc_device_addr; int /*<<< orphan*/  dma_desc_buffer; TYPE_1__* mmc; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int max_blk_count; } ;

/* Variables and functions */
 int BM_SOFT_RESET ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ SDMMC_BLKLEN ; 
 scalar_t__ SDMMC_BUSMODE ; 
 scalar_t__ SDMMC_STS0 ; 
 scalar_t__ SDMMC_STS1 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wmt_mci_priv*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct wmt_mci_priv* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readb (scalar_t__) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int wmt_mci_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc;
	struct wmt_mci_priv *priv;
	struct resource *res;
	u32 reg_tmp;

	mmc = platform_get_drvdata(pdev);
	priv = mmc_priv(mmc);

	/* reset SD controller */
	reg_tmp = readb(priv->sdmmc_base + SDMMC_BUSMODE);
	writel(reg_tmp | BM_SOFT_RESET, priv->sdmmc_base + SDMMC_BUSMODE);
	reg_tmp = readw(priv->sdmmc_base + SDMMC_BLKLEN);
	writew(reg_tmp & ~(0xA000), priv->sdmmc_base + SDMMC_BLKLEN);
	writeb(0xFF, priv->sdmmc_base + SDMMC_STS0);
	writeb(0xFF, priv->sdmmc_base + SDMMC_STS1);

	/* release the dma buffers */
	dma_free_coherent(&pdev->dev, priv->mmc->max_blk_count * 16,
			  priv->dma_desc_buffer, priv->dma_desc_device_addr);

	mmc_remove_host(mmc);

	free_irq(priv->irq_regular, priv);
	free_irq(priv->irq_dma, priv);

	iounmap(priv->sdmmc_base);

	clk_disable_unprepare(priv->clk_sdmmc);
	clk_put(priv->clk_sdmmc);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	mmc_free_host(mmc);

	dev_info(&pdev->dev, "WMT MCI device removed\n");

	return 0;
}