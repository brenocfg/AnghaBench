#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct cppi_glue_infos {int /*<<< orphan*/  first_completion_queue; int /*<<< orphan*/  qmgr_num_pend; int /*<<< orphan*/  td_queue; int /*<<< orphan*/  queues_tx; int /*<<< orphan*/  queues_rx; } ;
struct TYPE_6__ {int directions; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; struct device* dev; int /*<<< orphan*/  residue_granularity; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; } ;
struct cppi41_dd {int irq; TYPE_2__ ddev; int /*<<< orphan*/  n_chans; int /*<<< orphan*/  first_completion_queue; int /*<<< orphan*/  qmgr_num_pend; int /*<<< orphan*/  td_queue; int /*<<< orphan*/  queues_tx; int /*<<< orphan*/  queues_rx; int /*<<< orphan*/  pending; int /*<<< orphan*/  lock; void* qmgr_mem; void* sched_mem; void* ctrl_mem; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_cap; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 void* CPPI41_DMA_BUSWIDTHS ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_BURST ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 TYPE_1__ cpp41_dma_info ; 
 int cppi41_add_chans (struct device*,struct cppi41_dd*) ; 
 int /*<<< orphan*/  cppi41_dma_alloc_chan_resources ; 
 int /*<<< orphan*/  cppi41_dma_free_chan_resources ; 
 int /*<<< orphan*/  cppi41_dma_issue_pending ; 
 int /*<<< orphan*/  cppi41_dma_prep_slave_sg ; 
 int /*<<< orphan*/  cppi41_dma_tx_status ; 
 int /*<<< orphan*/  cppi41_dma_xlate ; 
 int /*<<< orphan*/  cppi41_irq ; 
 int /*<<< orphan*/  cppi41_stop_chan ; 
 int /*<<< orphan*/  deinit_cppi41 (struct device*,struct cppi41_dd*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct cppi41_dd* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cppi41_dd*) ; 
 int dma_async_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cppi_glue_infos* get_glue_info (struct device*) ; 
 int init_cppi41 (struct device*,struct cppi41_dd*) ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_dma_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int of_property_match_string (int /*<<< orphan*/ ,char*,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cppi41_dd*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cppi41_dma_probe(struct platform_device *pdev)
{
	struct cppi41_dd *cdd;
	struct device *dev = &pdev->dev;
	const struct cppi_glue_infos *glue_info;
	struct resource *mem;
	int index;
	int irq;
	int ret;

	glue_info = get_glue_info(dev);
	if (!glue_info)
		return -EINVAL;

	cdd = devm_kzalloc(&pdev->dev, sizeof(*cdd), GFP_KERNEL);
	if (!cdd)
		return -ENOMEM;

	dma_cap_set(DMA_SLAVE, cdd->ddev.cap_mask);
	cdd->ddev.device_alloc_chan_resources = cppi41_dma_alloc_chan_resources;
	cdd->ddev.device_free_chan_resources = cppi41_dma_free_chan_resources;
	cdd->ddev.device_tx_status = cppi41_dma_tx_status;
	cdd->ddev.device_issue_pending = cppi41_dma_issue_pending;
	cdd->ddev.device_prep_slave_sg = cppi41_dma_prep_slave_sg;
	cdd->ddev.device_terminate_all = cppi41_stop_chan;
	cdd->ddev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	cdd->ddev.src_addr_widths = CPPI41_DMA_BUSWIDTHS;
	cdd->ddev.dst_addr_widths = CPPI41_DMA_BUSWIDTHS;
	cdd->ddev.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	cdd->ddev.dev = dev;
	INIT_LIST_HEAD(&cdd->ddev.channels);
	cpp41_dma_info.dma_cap = cdd->ddev.cap_mask;

	index = of_property_match_string(dev->of_node,
					 "reg-names", "controller");
	if (index < 0)
		return index;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, index);
	cdd->ctrl_mem = devm_ioremap_resource(dev, mem);
	if (IS_ERR(cdd->ctrl_mem))
		return PTR_ERR(cdd->ctrl_mem);

	mem = platform_get_resource(pdev, IORESOURCE_MEM, index + 1);
	cdd->sched_mem = devm_ioremap_resource(dev, mem);
	if (IS_ERR(cdd->sched_mem))
		return PTR_ERR(cdd->sched_mem);

	mem = platform_get_resource(pdev, IORESOURCE_MEM, index + 2);
	cdd->qmgr_mem = devm_ioremap_resource(dev, mem);
	if (IS_ERR(cdd->qmgr_mem))
		return PTR_ERR(cdd->qmgr_mem);

	spin_lock_init(&cdd->lock);
	INIT_LIST_HEAD(&cdd->pending);

	platform_set_drvdata(pdev, cdd);

	pm_runtime_enable(dev);
	pm_runtime_set_autosuspend_delay(dev, 100);
	pm_runtime_use_autosuspend(dev);
	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		goto err_get_sync;

	cdd->queues_rx = glue_info->queues_rx;
	cdd->queues_tx = glue_info->queues_tx;
	cdd->td_queue = glue_info->td_queue;
	cdd->qmgr_num_pend = glue_info->qmgr_num_pend;
	cdd->first_completion_queue = glue_info->first_completion_queue;

	ret = of_property_read_u32(dev->of_node,
				   "#dma-channels", &cdd->n_chans);
	if (ret)
		goto err_get_n_chans;

	ret = init_cppi41(dev, cdd);
	if (ret)
		goto err_init_cppi;

	ret = cppi41_add_chans(dev, cdd);
	if (ret)
		goto err_chans;

	irq = irq_of_parse_and_map(dev->of_node, 0);
	if (!irq) {
		ret = -EINVAL;
		goto err_chans;
	}

	ret = devm_request_irq(&pdev->dev, irq, cppi41_irq, IRQF_SHARED,
			dev_name(dev), cdd);
	if (ret)
		goto err_chans;
	cdd->irq = irq;

	ret = dma_async_device_register(&cdd->ddev);
	if (ret)
		goto err_chans;

	ret = of_dma_controller_register(dev->of_node,
			cppi41_dma_xlate, &cpp41_dma_info);
	if (ret)
		goto err_of;

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return 0;
err_of:
	dma_async_device_unregister(&cdd->ddev);
err_chans:
	deinit_cppi41(dev, cdd);
err_init_cppi:
	pm_runtime_dont_use_autosuspend(dev);
err_get_n_chans:
err_get_sync:
	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);
	return ret;
}