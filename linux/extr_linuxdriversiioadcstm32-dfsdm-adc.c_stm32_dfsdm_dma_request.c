#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stm32_dfsdm_adc {TYPE_3__* dma_chan; int /*<<< orphan*/  dma_buf; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  fl_id; TYPE_1__* dfsdm; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct dma_slave_config {int /*<<< orphan*/  src_addr_width; scalar_t__ src_addr; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_8__ {TYPE_2__* device; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  phys_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_DMA_BUFFER_SIZE ; 
 scalar_t__ DFSDM_RDATAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_3__*) ; 
 TYPE_3__* dma_request_slave_channel (int /*<<< orphan*/ *,char*) ; 
 int dmaengine_slave_config (TYPE_3__*,struct dma_slave_config*) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int stm32_dfsdm_dma_request(struct iio_dev *indio_dev)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	struct dma_slave_config config = {
		.src_addr = (dma_addr_t)adc->dfsdm->phys_base +
			DFSDM_RDATAR(adc->fl_id),
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
	};
	int ret;

	adc->dma_chan = dma_request_slave_channel(&indio_dev->dev, "rx");
	if (!adc->dma_chan)
		return -EINVAL;

	adc->rx_buf = dma_alloc_coherent(adc->dma_chan->device->dev,
					 DFSDM_DMA_BUFFER_SIZE,
					 &adc->dma_buf, GFP_KERNEL);
	if (!adc->rx_buf) {
		ret = -ENOMEM;
		goto err_release;
	}

	ret = dmaengine_slave_config(adc->dma_chan, &config);
	if (ret)
		goto err_free;

	return 0;

err_free:
	dma_free_coherent(adc->dma_chan->device->dev, DFSDM_DMA_BUFFER_SIZE,
			  adc->rx_buf, adc->dma_buf);
err_release:
	dma_release_channel(adc->dma_chan);

	return ret;
}