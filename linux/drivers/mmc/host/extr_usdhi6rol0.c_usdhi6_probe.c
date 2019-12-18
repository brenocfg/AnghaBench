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
struct usdhi6_host {int imclk; void* clk; int /*<<< orphan*/  timeout_work; void* base; void* pins_default; void* pinctrl; void* pins_uhs; int /*<<< orphan*/  timeout; int /*<<< orphan*/  wait; struct mmc_host* mmc; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct mmc_host {int caps; int max_segs; int max_blk_size; int max_req_size; int max_blk_count; int max_seg_size; int f_max; int f_min; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int MMC_CAP_MMC_HIGHSPEED ; 
 int MMC_CAP_NEEDS_POLL ; 
 int MMC_CAP_SDIO_IRQ ; 
 int MMC_CAP_SD_HIGHSPEED ; 
 int PAGE_SIZE ; 
 char* PINCTRL_STATE_DEFAULT ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  USDHI6_SD_PORT_SEL ; 
 int USDHI6_SD_PORT_SEL_PORTS_SHIFT ; 
 int /*<<< orphan*/  USDHI6_VERSION ; 
 int /*<<< orphan*/  USDHI6_WAIT_FOR_REQUEST ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_pinctrl_get (struct device*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usdhi6_host*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usdhi6_host*) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,struct device*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 struct usdhi6_host* mmc_priv (struct mmc_host*) ; 
 int mmc_regulator_get_supply (struct mmc_host*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 void* pinctrl_lookup_state (void*,char*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usdhi6_host*) ; 
 int /*<<< orphan*/  usdhi6_cd ; 
 int /*<<< orphan*/  usdhi6_dma_request (struct usdhi6_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usdhi6_mask_all (struct usdhi6_host*) ; 
 int /*<<< orphan*/  usdhi6_ops ; 
 int usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usdhi6_sd ; 
 int /*<<< orphan*/  usdhi6_sd_bh ; 
 int /*<<< orphan*/  usdhi6_sdio ; 
 int /*<<< orphan*/  usdhi6_timeout_work ; 

__attribute__((used)) static int usdhi6_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mmc_host *mmc;
	struct usdhi6_host *host;
	struct resource *res;
	int irq_cd, irq_sd, irq_sdio;
	u32 version;
	int ret;

	if (!dev->of_node)
		return -ENODEV;

	irq_cd = platform_get_irq_byname(pdev, "card detect");
	irq_sd = platform_get_irq_byname(pdev, "data");
	irq_sdio = platform_get_irq_byname(pdev, "SDIO");
	if (irq_sd < 0 || irq_sdio < 0)
		return -ENODEV;

	mmc = mmc_alloc_host(sizeof(struct usdhi6_host), dev);
	if (!mmc)
		return -ENOMEM;

	ret = mmc_regulator_get_supply(mmc);
	if (ret)
		goto e_free_mmc;

	ret = mmc_of_parse(mmc);
	if (ret < 0)
		goto e_free_mmc;

	host		= mmc_priv(mmc);
	host->mmc	= mmc;
	host->wait	= USDHI6_WAIT_FOR_REQUEST;
	host->timeout	= msecs_to_jiffies(4000);

	host->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(host->pinctrl)) {
		ret = PTR_ERR(host->pinctrl);
		goto e_free_mmc;
	}

	host->pins_uhs = pinctrl_lookup_state(host->pinctrl, "state_uhs");
	if (!IS_ERR(host->pins_uhs)) {
		host->pins_default = pinctrl_lookup_state(host->pinctrl,
							  PINCTRL_STATE_DEFAULT);

		if (IS_ERR(host->pins_default)) {
			dev_err(dev,
				"UHS pinctrl requires a default pin state.\n");
			ret = PTR_ERR(host->pins_default);
			goto e_free_mmc;
		}
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(host->base)) {
		ret = PTR_ERR(host->base);
		goto e_free_mmc;
	}

	host->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(host->clk)) {
		ret = PTR_ERR(host->clk);
		goto e_free_mmc;
	}

	host->imclk = clk_get_rate(host->clk);

	ret = clk_prepare_enable(host->clk);
	if (ret < 0)
		goto e_free_mmc;

	version = usdhi6_read(host, USDHI6_VERSION);
	if ((version & 0xfff) != 0xa0d) {
		dev_err(dev, "Version not recognized %x\n", version);
		goto e_clk_off;
	}

	dev_info(dev, "A USDHI6ROL0 SD host detected with %d ports\n",
		 usdhi6_read(host, USDHI6_SD_PORT_SEL) >> USDHI6_SD_PORT_SEL_PORTS_SHIFT);

	usdhi6_mask_all(host);

	if (irq_cd >= 0) {
		ret = devm_request_irq(dev, irq_cd, usdhi6_cd, 0,
				       dev_name(dev), host);
		if (ret < 0)
			goto e_clk_off;
	} else {
		mmc->caps |= MMC_CAP_NEEDS_POLL;
	}

	ret = devm_request_threaded_irq(dev, irq_sd, usdhi6_sd, usdhi6_sd_bh, 0,
			       dev_name(dev), host);
	if (ret < 0)
		goto e_clk_off;

	ret = devm_request_irq(dev, irq_sdio, usdhi6_sdio, 0,
			       dev_name(dev), host);
	if (ret < 0)
		goto e_clk_off;

	INIT_DELAYED_WORK(&host->timeout_work, usdhi6_timeout_work);

	usdhi6_dma_request(host, res->start);

	mmc->ops = &usdhi6_ops;
	mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED |
		     MMC_CAP_SDIO_IRQ;
	/* Set .max_segs to some random number. Feel free to adjust. */
	mmc->max_segs = 32;
	mmc->max_blk_size = 512;
	mmc->max_req_size = PAGE_SIZE * mmc->max_segs;
	mmc->max_blk_count = mmc->max_req_size / mmc->max_blk_size;
	/*
	 * Setting .max_seg_size to 1 page would simplify our page-mapping code,
	 * But OTOH, having large segments makes DMA more efficient. We could
	 * check, whether we managed to get DMA and fall back to 1 page
	 * segments, but if we do manage to obtain DMA and then it fails at
	 * run-time and we fall back to PIO, we will continue getting large
	 * segments. So, we wouldn't be able to get rid of the code anyway.
	 */
	mmc->max_seg_size = mmc->max_req_size;
	if (!mmc->f_max)
		mmc->f_max = host->imclk;
	mmc->f_min = host->imclk / 512;

	platform_set_drvdata(pdev, host);

	ret = mmc_add_host(mmc);
	if (ret < 0)
		goto e_clk_off;

	return 0;

e_clk_off:
	clk_disable_unprepare(host->clk);
e_free_mmc:
	mmc_free_host(mmc);

	return ret;
}