#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct mt_gpdma_desc {int dummy; } ;
struct mt_bdma_desc {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  bd_addr; void* bd; int /*<<< orphan*/  gpd_addr; void* gpd; } ;
struct msdc_host {scalar_t__ irq; int internal_cd; int timeout_clks; TYPE_8__ dma; TYPE_1__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  req_timeout; void* dma_mask; TYPE_6__* dev_comp; int /*<<< orphan*/  src_clk_freq; int /*<<< orphan*/ * src_clk; struct mmc_host* mmc; int /*<<< orphan*/ * pins_uhs; int /*<<< orphan*/ * pinctrl; int /*<<< orphan*/ * pins_default; int /*<<< orphan*/ * src_clk_cg; int /*<<< orphan*/ * bus_clk; int /*<<< orphan*/ * h_clk; int /*<<< orphan*/ * top_base; int /*<<< orphan*/ * base; } ;
struct mmc_host {int caps; int max_segs; int max_blk_size; int max_req_size; int max_blk_count; int /*<<< orphan*/  max_seg_size; int /*<<< orphan*/  caps2; void* f_min; int /*<<< orphan*/ * ops; } ;
struct TYPE_21__ {void** dma_mask; } ;
struct TYPE_19__ {int clk_div_bits; scalar_t__ support_64g; scalar_t__ use_internal_cd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDMA_DESC_BUFLEN ; 
 int /*<<< orphan*/  BDMA_DESC_BUFLEN_EXT ; 
 void* DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 void* DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MAX_BD_NUM ; 
 int /*<<< orphan*/  MMC_CAP2_SDIO_IRQ_NOTHREAD ; 
 int MMC_CAP_CMD23 ; 
 int MMC_CAP_ERASE ; 
 int MMC_CAP_NONREMOVABLE ; 
 int MMC_CAP_SDIO_IRQ ; 
 int /*<<< orphan*/  MTK_MMC_AUTOSUSPEND_DELAY ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 void* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/ * devm_pinctrl_get (TYPE_1__*) ; 
 int devm_request_irq (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msdc_host*) ; 
 void* dma_alloc_coherent (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (TYPE_1__*,int,void*,int /*<<< orphan*/ ) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_can_gpio_cd (struct mmc_host*) ; 
 TYPE_9__* mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int mmc_regulator_get_supply (struct mmc_host*) ; 
 int /*<<< orphan*/  msdc_deinit_hw (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_gate_clock (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_init_gpd_bd (struct msdc_host*,TYPE_8__*) ; 
 int /*<<< orphan*/  msdc_init_hw (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_irq ; 
 int /*<<< orphan*/  msdc_of_property_parse (struct platform_device*,struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_request_timeout ; 
 int /*<<< orphan*/  msdc_ungate_clock (struct msdc_host*) ; 
 int /*<<< orphan*/  mt_msdc_ops ; 
 TYPE_6__* of_device_get_match_data (TYPE_1__*) ; 
 void* pinctrl_lookup_state (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_host*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msdc_drv_probe(struct platform_device *pdev)
{
	struct mmc_host *mmc;
	struct msdc_host *host;
	struct resource *res;
	int ret;

	if (!pdev->dev.of_node) {
		dev_err(&pdev->dev, "No DT found\n");
		return -EINVAL;
	}

	/* Allocate MMC host for this device */
	mmc = mmc_alloc_host(sizeof(struct msdc_host), &pdev->dev);
	if (!mmc)
		return -ENOMEM;

	host = mmc_priv(mmc);
	ret = mmc_of_parse(mmc);
	if (ret)
		goto host_free;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(host->base)) {
		ret = PTR_ERR(host->base);
		goto host_free;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (res) {
		host->top_base = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(host->top_base))
			host->top_base = NULL;
	}

	ret = mmc_regulator_get_supply(mmc);
	if (ret)
		goto host_free;

	host->src_clk = devm_clk_get(&pdev->dev, "source");
	if (IS_ERR(host->src_clk)) {
		ret = PTR_ERR(host->src_clk);
		goto host_free;
	}

	host->h_clk = devm_clk_get(&pdev->dev, "hclk");
	if (IS_ERR(host->h_clk)) {
		ret = PTR_ERR(host->h_clk);
		goto host_free;
	}

	host->bus_clk = devm_clk_get(&pdev->dev, "bus_clk");
	if (IS_ERR(host->bus_clk))
		host->bus_clk = NULL;
	/*source clock control gate is optional clock*/
	host->src_clk_cg = devm_clk_get(&pdev->dev, "source_cg");
	if (IS_ERR(host->src_clk_cg))
		host->src_clk_cg = NULL;

	host->irq = platform_get_irq(pdev, 0);
	if (host->irq < 0) {
		ret = -EINVAL;
		goto host_free;
	}

	host->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(host->pinctrl)) {
		ret = PTR_ERR(host->pinctrl);
		dev_err(&pdev->dev, "Cannot find pinctrl!\n");
		goto host_free;
	}

	host->pins_default = pinctrl_lookup_state(host->pinctrl, "default");
	if (IS_ERR(host->pins_default)) {
		ret = PTR_ERR(host->pins_default);
		dev_err(&pdev->dev, "Cannot find pinctrl default!\n");
		goto host_free;
	}

	host->pins_uhs = pinctrl_lookup_state(host->pinctrl, "state_uhs");
	if (IS_ERR(host->pins_uhs)) {
		ret = PTR_ERR(host->pins_uhs);
		dev_err(&pdev->dev, "Cannot find pinctrl uhs!\n");
		goto host_free;
	}

	msdc_of_property_parse(pdev, host);

	host->dev = &pdev->dev;
	host->dev_comp = of_device_get_match_data(&pdev->dev);
	host->mmc = mmc;
	host->src_clk_freq = clk_get_rate(host->src_clk);
	/* Set host parameters to mmc */
	mmc->ops = &mt_msdc_ops;
	if (host->dev_comp->clk_div_bits == 8)
		mmc->f_min = DIV_ROUND_UP(host->src_clk_freq, 4 * 255);
	else
		mmc->f_min = DIV_ROUND_UP(host->src_clk_freq, 4 * 4095);

	if (!(mmc->caps & MMC_CAP_NONREMOVABLE) &&
	    !mmc_can_gpio_cd(mmc) &&
	    host->dev_comp->use_internal_cd) {
		/*
		 * Is removable but no GPIO declared, so
		 * use internal functionality.
		 */
		host->internal_cd = true;
	}

	if (mmc->caps & MMC_CAP_SDIO_IRQ)
		mmc->caps2 |= MMC_CAP2_SDIO_IRQ_NOTHREAD;

	mmc->caps |= MMC_CAP_ERASE | MMC_CAP_CMD23;
	/* MMC core transfer sizes tunable parameters */
	mmc->max_segs = MAX_BD_NUM;
	if (host->dev_comp->support_64g)
		mmc->max_seg_size = BDMA_DESC_BUFLEN_EXT;
	else
		mmc->max_seg_size = BDMA_DESC_BUFLEN;
	mmc->max_blk_size = 2048;
	mmc->max_req_size = 512 * 1024;
	mmc->max_blk_count = mmc->max_req_size / 512;
	if (host->dev_comp->support_64g)
		host->dma_mask = DMA_BIT_MASK(36);
	else
		host->dma_mask = DMA_BIT_MASK(32);
	mmc_dev(mmc)->dma_mask = &host->dma_mask;

	host->timeout_clks = 3 * 1048576;
	host->dma.gpd = dma_alloc_coherent(&pdev->dev,
				2 * sizeof(struct mt_gpdma_desc),
				&host->dma.gpd_addr, GFP_KERNEL);
	host->dma.bd = dma_alloc_coherent(&pdev->dev,
				MAX_BD_NUM * sizeof(struct mt_bdma_desc),
				&host->dma.bd_addr, GFP_KERNEL);
	if (!host->dma.gpd || !host->dma.bd) {
		ret = -ENOMEM;
		goto release_mem;
	}
	msdc_init_gpd_bd(host, &host->dma);
	INIT_DELAYED_WORK(&host->req_timeout, msdc_request_timeout);
	spin_lock_init(&host->lock);

	platform_set_drvdata(pdev, mmc);
	msdc_ungate_clock(host);
	msdc_init_hw(host);

	ret = devm_request_irq(&pdev->dev, host->irq, msdc_irq,
			       IRQF_TRIGGER_NONE, pdev->name, host);
	if (ret)
		goto release;

	pm_runtime_set_active(host->dev);
	pm_runtime_set_autosuspend_delay(host->dev, MTK_MMC_AUTOSUSPEND_DELAY);
	pm_runtime_use_autosuspend(host->dev);
	pm_runtime_enable(host->dev);
	ret = mmc_add_host(mmc);

	if (ret)
		goto end;

	return 0;
end:
	pm_runtime_disable(host->dev);
release:
	platform_set_drvdata(pdev, NULL);
	msdc_deinit_hw(host);
	msdc_gate_clock(host);
release_mem:
	if (host->dma.gpd)
		dma_free_coherent(&pdev->dev,
			2 * sizeof(struct mt_gpdma_desc),
			host->dma.gpd, host->dma.gpd_addr);
	if (host->dma.bd)
		dma_free_coherent(&pdev->dev,
			MAX_BD_NUM * sizeof(struct mt_bdma_desc),
			host->dma.bd, host->dma.bd_addr);
host_free:
	mmc_free_host(mmc);

	return ret;
}