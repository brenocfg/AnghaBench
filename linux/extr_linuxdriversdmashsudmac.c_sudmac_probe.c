#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sudmac_pdata {int channel_num; } ;
struct dma_device {int /*<<< orphan*/  cap_mask; } ;
struct TYPE_3__ {int desc_size; struct dma_device dma_dev; int /*<<< orphan*/ * ops; } ;
struct sudmac_device {TYPE_1__ shdma_dev; void* pdata; int /*<<< orphan*/  chan_reg; } ;
struct sudmac_desc {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct sudmac_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sudmac_device*) ; 
 int /*<<< orphan*/  shdma_cleanup (TYPE_1__*) ; 
 int shdma_init (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int sudmac_chan_probe (struct sudmac_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sudmac_chan_remove (struct sudmac_device*) ; 
 int /*<<< orphan*/  sudmac_shdma_ops ; 

__attribute__((used)) static int sudmac_probe(struct platform_device *pdev)
{
	struct sudmac_pdata *pdata = dev_get_platdata(&pdev->dev);
	int err, i;
	struct sudmac_device *su_dev;
	struct dma_device *dma_dev;
	struct resource *chan, *irq_res;

	/* get platform data */
	if (!pdata)
		return -ENODEV;

	irq_res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq_res)
		return -ENODEV;

	err = -ENOMEM;
	su_dev = devm_kzalloc(&pdev->dev, sizeof(struct sudmac_device),
			      GFP_KERNEL);
	if (!su_dev)
		return err;

	dma_dev = &su_dev->shdma_dev.dma_dev;

	chan = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	su_dev->chan_reg = devm_ioremap_resource(&pdev->dev, chan);
	if (IS_ERR(su_dev->chan_reg))
		return PTR_ERR(su_dev->chan_reg);

	dma_cap_set(DMA_SLAVE, dma_dev->cap_mask);

	su_dev->shdma_dev.ops = &sudmac_shdma_ops;
	su_dev->shdma_dev.desc_size = sizeof(struct sudmac_desc);
	err = shdma_init(&pdev->dev, &su_dev->shdma_dev, pdata->channel_num);
	if (err < 0)
		return err;

	/* platform data */
	su_dev->pdata = dev_get_platdata(&pdev->dev);

	platform_set_drvdata(pdev, su_dev);

	/* Create DMA Channel */
	for (i = 0; i < pdata->channel_num; i++) {
		err = sudmac_chan_probe(su_dev, i, irq_res->start, IRQF_SHARED);
		if (err)
			goto chan_probe_err;
	}

	err = dma_async_device_register(&su_dev->shdma_dev.dma_dev);
	if (err < 0)
		goto chan_probe_err;

	return err;

chan_probe_err:
	sudmac_chan_remove(su_dev);

	shdma_cleanup(&su_dev->shdma_dev);

	return err;
}