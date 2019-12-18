#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_11__ {struct omap_mmc_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct omap_mmc_platform_data {int nr_slots; int (* init ) (TYPE_2__*) ;int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;TYPE_1__* slots; } ;
struct mmc_omap_host {int irq; int dma_tx_burst; int dma_rx_burst; int nr_slots; int reg_shift; int /*<<< orphan*/ * iclk; int /*<<< orphan*/ * fclk; int /*<<< orphan*/ * dma_rx; int /*<<< orphan*/ * dma_tx; int /*<<< orphan*/  mmc_omap_wq; int /*<<< orphan*/ * slots; TYPE_2__* dev; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  id; struct omap_mmc_platform_data* pdata; int /*<<< orphan*/  features; int /*<<< orphan*/  slot_wq; int /*<<< orphan*/  slot_lock; int /*<<< orphan*/  dma_lock; int /*<<< orphan*/  clk_timer; int /*<<< orphan*/  clk_lock; int /*<<< orphan*/  cmd_abort_timer; int /*<<< orphan*/  cmd_abort_work; int /*<<< orphan*/  send_stop_work; int /*<<< orphan*/  slot_release_work; int /*<<< orphan*/ * virt_base; } ;
struct TYPE_10__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ *) ; 
 void* clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct mmc_omap_host* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 void* dma_request_chan (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free_irq (int,struct mmc_omap_host*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ mmc_omap7xx () ; 
 int /*<<< orphan*/  mmc_omap_abort_command ; 
 int /*<<< orphan*/  mmc_omap_clk_timer ; 
 int /*<<< orphan*/  mmc_omap_cmd_timer ; 
 int /*<<< orphan*/  mmc_omap_irq ; 
 int mmc_omap_new_slot (struct mmc_omap_host*,int) ; 
 int /*<<< orphan*/  mmc_omap_remove_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_omap_send_stop_work ; 
 int /*<<< orphan*/  mmc_omap_slot_release_work ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_omap_host*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_omap_host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_omap_probe(struct platform_device *pdev)
{
	struct omap_mmc_platform_data *pdata = pdev->dev.platform_data;
	struct mmc_omap_host *host = NULL;
	struct resource *res;
	int i, ret = 0;
	int irq;

	if (pdata == NULL) {
		dev_err(&pdev->dev, "platform data missing\n");
		return -ENXIO;
	}
	if (pdata->nr_slots == 0) {
		dev_err(&pdev->dev, "no slots\n");
		return -EPROBE_DEFER;
	}

	host = devm_kzalloc(&pdev->dev, sizeof(struct mmc_omap_host),
			    GFP_KERNEL);
	if (host == NULL)
		return -ENOMEM;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -ENXIO;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->virt_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(host->virt_base))
		return PTR_ERR(host->virt_base);

	INIT_WORK(&host->slot_release_work, mmc_omap_slot_release_work);
	INIT_WORK(&host->send_stop_work, mmc_omap_send_stop_work);

	INIT_WORK(&host->cmd_abort_work, mmc_omap_abort_command);
	timer_setup(&host->cmd_abort_timer, mmc_omap_cmd_timer, 0);

	spin_lock_init(&host->clk_lock);
	timer_setup(&host->clk_timer, mmc_omap_clk_timer, 0);

	spin_lock_init(&host->dma_lock);
	spin_lock_init(&host->slot_lock);
	init_waitqueue_head(&host->slot_wq);

	host->pdata = pdata;
	host->features = host->pdata->slots[0].features;
	host->dev = &pdev->dev;
	platform_set_drvdata(pdev, host);

	host->id = pdev->id;
	host->irq = irq;
	host->phys_base = res->start;
	host->iclk = clk_get(&pdev->dev, "ick");
	if (IS_ERR(host->iclk))
		return PTR_ERR(host->iclk);
	clk_enable(host->iclk);

	host->fclk = clk_get(&pdev->dev, "fck");
	if (IS_ERR(host->fclk)) {
		ret = PTR_ERR(host->fclk);
		goto err_free_iclk;
	}

	host->dma_tx_burst = -1;
	host->dma_rx_burst = -1;

	host->dma_tx = dma_request_chan(&pdev->dev, "tx");
	if (IS_ERR(host->dma_tx)) {
		ret = PTR_ERR(host->dma_tx);
		if (ret == -EPROBE_DEFER) {
			clk_put(host->fclk);
			goto err_free_iclk;
		}

		host->dma_tx = NULL;
		dev_warn(host->dev, "TX DMA channel request failed\n");
	}

	host->dma_rx = dma_request_chan(&pdev->dev, "rx");
	if (IS_ERR(host->dma_rx)) {
		ret = PTR_ERR(host->dma_rx);
		if (ret == -EPROBE_DEFER) {
			if (host->dma_tx)
				dma_release_channel(host->dma_tx);
			clk_put(host->fclk);
			goto err_free_iclk;
		}

		host->dma_rx = NULL;
		dev_warn(host->dev, "RX DMA channel request failed\n");
	}

	ret = request_irq(host->irq, mmc_omap_irq, 0, DRIVER_NAME, host);
	if (ret)
		goto err_free_dma;

	if (pdata->init != NULL) {
		ret = pdata->init(&pdev->dev);
		if (ret < 0)
			goto err_free_irq;
	}

	host->nr_slots = pdata->nr_slots;
	host->reg_shift = (mmc_omap7xx() ? 1 : 2);

	host->mmc_omap_wq = alloc_workqueue("mmc_omap", 0, 0);
	if (!host->mmc_omap_wq) {
		ret = -ENOMEM;
		goto err_plat_cleanup;
	}

	for (i = 0; i < pdata->nr_slots; i++) {
		ret = mmc_omap_new_slot(host, i);
		if (ret < 0) {
			while (--i >= 0)
				mmc_omap_remove_slot(host->slots[i]);

			goto err_destroy_wq;
		}
	}

	return 0;

err_destroy_wq:
	destroy_workqueue(host->mmc_omap_wq);
err_plat_cleanup:
	if (pdata->cleanup)
		pdata->cleanup(&pdev->dev);
err_free_irq:
	free_irq(host->irq, host);
err_free_dma:
	if (host->dma_tx)
		dma_release_channel(host->dma_tx);
	if (host->dma_rx)
		dma_release_channel(host->dma_rx);
	clk_put(host->fclk);
err_free_iclk:
	clk_disable(host->iclk);
	clk_put(host->iclk);
	return ret;
}