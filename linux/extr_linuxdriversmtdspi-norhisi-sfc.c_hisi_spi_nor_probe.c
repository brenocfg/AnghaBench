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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hifmc_host {void* clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  dma_buffer; void* iobase; void* regbase; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIFMC_DMA_MAX_LEN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct hifmc_host* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_spi_nor_init (struct hifmc_host*) ; 
 int hisi_spi_nor_register_all (struct hifmc_host*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hifmc_host*) ; 

__attribute__((used)) static int hisi_spi_nor_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct hifmc_host *host;
	int ret;

	host = devm_kzalloc(dev, sizeof(*host), GFP_KERNEL);
	if (!host)
		return -ENOMEM;

	platform_set_drvdata(pdev, host);
	host->dev = dev;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "control");
	host->regbase = devm_ioremap_resource(dev, res);
	if (IS_ERR(host->regbase))
		return PTR_ERR(host->regbase);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "memory");
	host->iobase = devm_ioremap_resource(dev, res);
	if (IS_ERR(host->iobase))
		return PTR_ERR(host->iobase);

	host->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(host->clk))
		return PTR_ERR(host->clk);

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (ret) {
		dev_warn(dev, "Unable to set dma mask\n");
		return ret;
	}

	host->buffer = dmam_alloc_coherent(dev, HIFMC_DMA_MAX_LEN,
			&host->dma_buffer, GFP_KERNEL);
	if (!host->buffer)
		return -ENOMEM;

	ret = clk_prepare_enable(host->clk);
	if (ret)
		return ret;

	mutex_init(&host->lock);
	hisi_spi_nor_init(host);
	ret = hisi_spi_nor_register_all(host);
	if (ret)
		mutex_destroy(&host->lock);

	clk_disable_unprepare(host->clk);
	return ret;
}