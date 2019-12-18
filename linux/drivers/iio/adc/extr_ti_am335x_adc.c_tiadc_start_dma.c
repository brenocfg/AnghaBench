#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int src_maxburst; } ;
struct tiadc_dma {int fifo_thresh; int period_size; int /*<<< orphan*/  chan; int /*<<< orphan*/  cookie; int /*<<< orphan*/  addr; TYPE_1__ conf; scalar_t__ current_period; } ;
struct tiadc_device {int total_ch_enabled; struct tiadc_dma dma; } ;
struct iio_dev {int dummy; } ;
struct dma_async_tx_descriptor {struct iio_dev* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int DMA_FIFO1 ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int EBUSY ; 
 int FIFO1_THRESHOLD ; 
 int /*<<< orphan*/  REG_DMA1REQ ; 
 int /*<<< orphan*/  REG_DMAENABLE_SET ; 
 int /*<<< orphan*/  REG_FIFO1THR ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_dma_cyclic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_slave_config (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 void* rounddown (int,int) ; 
 int /*<<< orphan*/  tiadc_dma_rx_complete ; 
 int /*<<< orphan*/  tiadc_writel (struct tiadc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tiadc_start_dma(struct iio_dev *indio_dev)
{
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	struct tiadc_dma *dma = &adc_dev->dma;
	struct dma_async_tx_descriptor *desc;

	dma->current_period = 0; /* We start to fill period 0 */
	/*
	 * Make the fifo thresh as the multiple of total number of
	 * channels enabled, so make sure that cyclic DMA period
	 * length is also a multiple of total number of channels
	 * enabled. This ensures that no invalid data is reported
	 * to the stack via iio_push_to_buffers().
	 */
	dma->fifo_thresh = rounddown(FIFO1_THRESHOLD + 1,
				     adc_dev->total_ch_enabled) - 1;
	/* Make sure that period length is multiple of fifo thresh level */
	dma->period_size = rounddown(DMA_BUFFER_SIZE / 2,
				    (dma->fifo_thresh + 1) * sizeof(u16));

	dma->conf.src_maxburst = dma->fifo_thresh + 1;
	dmaengine_slave_config(dma->chan, &dma->conf);

	desc = dmaengine_prep_dma_cyclic(dma->chan, dma->addr,
					 dma->period_size * 2,
					 dma->period_size, DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT);
	if (!desc)
		return -EBUSY;

	desc->callback = tiadc_dma_rx_complete;
	desc->callback_param = indio_dev;

	dma->cookie = dmaengine_submit(desc);

	dma_async_issue_pending(dma->chan);

	tiadc_writel(adc_dev, REG_FIFO1THR, dma->fifo_thresh);
	tiadc_writel(adc_dev, REG_DMA1REQ, dma->fifo_thresh);
	tiadc_writel(adc_dev, REG_DMAENABLE_SET, DMA_FIFO1);

	return 0;
}