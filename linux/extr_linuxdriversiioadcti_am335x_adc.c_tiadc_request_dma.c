#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ src_addr; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  direction; } ;
struct tiadc_dma {TYPE_4__* chan; int /*<<< orphan*/  buf; int /*<<< orphan*/  addr; TYPE_1__ conf; } ;
struct tiadc_device {TYPE_2__* mfd_tscadc; struct tiadc_dma dma; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_11__ {TYPE_3__* device; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; scalar_t__ tscadc_phys_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 int PTR_ERR (TYPE_4__*) ; 
 scalar_t__ REG_FIFO1 ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_4__*) ; 
 TYPE_4__* dma_request_chan (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tiadc_request_dma(struct platform_device *pdev,
			     struct tiadc_device *adc_dev)
{
	struct tiadc_dma	*dma = &adc_dev->dma;
	dma_cap_mask_t		mask;

	/* Default slave configuration parameters */
	dma->conf.direction = DMA_DEV_TO_MEM;
	dma->conf.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	dma->conf.src_addr = adc_dev->mfd_tscadc->tscadc_phys_base + REG_FIFO1;

	dma_cap_zero(mask);
	dma_cap_set(DMA_CYCLIC, mask);

	/* Get a channel for RX */
	dma->chan = dma_request_chan(adc_dev->mfd_tscadc->dev, "fifo1");
	if (IS_ERR(dma->chan)) {
		int ret = PTR_ERR(dma->chan);

		dma->chan = NULL;
		return ret;
	}

	/* RX buffer */
	dma->buf = dma_alloc_coherent(dma->chan->device->dev, DMA_BUFFER_SIZE,
				      &dma->addr, GFP_KERNEL);
	if (!dma->buf)
		goto err;

	return 0;
err:
	dma_release_channel(dma->chan);
	return -ENOMEM;
}