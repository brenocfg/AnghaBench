#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stm32_dfsdm_adc {TYPE_2__* dma_chan; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  dma_buf; } ;
struct iio_dev {int /*<<< orphan*/ * setup_ops; int /*<<< orphan*/  modes; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_DMA_BUFFER_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDIO_BUFFER_SOFTWARE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_2__*) ; 
 TYPE_2__* dma_request_slave_channel (int /*<<< orphan*/ *,char*) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  stm32_dfsdm_buffer_setup_ops ; 

__attribute__((used)) static int stm32_dfsdm_dma_request(struct iio_dev *indio_dev)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);

	adc->dma_chan = dma_request_slave_channel(&indio_dev->dev, "rx");
	if (!adc->dma_chan)
		return -EINVAL;

	adc->rx_buf = dma_alloc_coherent(adc->dma_chan->device->dev,
					 DFSDM_DMA_BUFFER_SIZE,
					 &adc->dma_buf, GFP_KERNEL);
	if (!adc->rx_buf) {
		dma_release_channel(adc->dma_chan);
		return -ENOMEM;
	}

	indio_dev->modes |= INDIO_BUFFER_SOFTWARE;
	indio_dev->setup_ops = &stm32_dfsdm_buffer_setup_ops;

	return 0;
}