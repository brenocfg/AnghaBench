#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;
struct TYPE_6__ {TYPE_3__* dma_chan; int /*<<< orphan*/  rx_dma_buf; int /*<<< orphan*/  rx_buf; } ;
struct at91_adc_state {TYPE_2__ dma_st; } ;
struct TYPE_7__ {TYPE_1__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AT91_BUFFER_MAX_CONVERSION_BYTES ; 
 int AT91_HWFIFO_MAX_SIZE ; 
 unsigned int DIV_ROUND_UP (int,unsigned int) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_3__*) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (TYPE_3__*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void at91_adc_dma_disable(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct at91_adc_state *st = iio_priv(indio_dev);
	unsigned int pages = DIV_ROUND_UP(AT91_HWFIFO_MAX_SIZE *
					  AT91_BUFFER_MAX_CONVERSION_BYTES * 2,
					  PAGE_SIZE);

	/* if we are not using DMA, just return */
	if (!st->dma_st.dma_chan)
		return;

	/* wait for all transactions to be terminated first*/
	dmaengine_terminate_sync(st->dma_st.dma_chan);

	dma_free_coherent(st->dma_st.dma_chan->device->dev, pages * PAGE_SIZE,
			  st->dma_st.rx_buf, st->dma_st.rx_dma_buf);
	dma_release_channel(st->dma_st.dma_chan);
	st->dma_st.dma_chan = 0;

	dev_info(&pdev->dev, "continuing without DMA support\n");
}