#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;
struct dma_slave_config {int src_maxburst; int dst_maxburst; int /*<<< orphan*/  src_addr_width; scalar_t__ src_addr; int /*<<< orphan*/  direction; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {TYPE_3__* dma_chan; int /*<<< orphan*/  rx_dma_buf; int /*<<< orphan*/  rx_buf; scalar_t__ phys_addr; } ;
struct at91_adc_state {TYPE_2__ dma_st; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_9__ {TYPE_1__* device; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AT91_BUFFER_MAX_CONVERSION_BYTES ; 
 int AT91_HWFIFO_MAX_SIZE ; 
 scalar_t__ AT91_SAMA5D2_LCDR ; 
 unsigned int DIV_ROUND_UP (int,unsigned int) ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_chan_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_3__*) ; 
 TYPE_3__* dma_request_slave_channel (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dmaengine_slave_config (TYPE_3__*,struct dma_slave_config*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void at91_adc_dma_init(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct at91_adc_state *st = iio_priv(indio_dev);
	struct dma_slave_config config = {0};
	/*
	 * We make the buffer double the size of the fifo,
	 * such that DMA uses one half of the buffer (full fifo size)
	 * and the software uses the other half to read/write.
	 */
	unsigned int pages = DIV_ROUND_UP(AT91_HWFIFO_MAX_SIZE *
					  AT91_BUFFER_MAX_CONVERSION_BYTES * 2,
					  PAGE_SIZE);

	if (st->dma_st.dma_chan)
		return;

	st->dma_st.dma_chan = dma_request_slave_channel(&pdev->dev, "rx");

	if (!st->dma_st.dma_chan)  {
		dev_info(&pdev->dev, "can't get DMA channel\n");
		goto dma_exit;
	}

	st->dma_st.rx_buf = dma_alloc_coherent(st->dma_st.dma_chan->device->dev,
					       pages * PAGE_SIZE,
					       &st->dma_st.rx_dma_buf,
					       GFP_KERNEL);
	if (!st->dma_st.rx_buf) {
		dev_info(&pdev->dev, "can't allocate coherent DMA area\n");
		goto dma_chan_disable;
	}

	/* Configure DMA channel to read data register */
	config.direction = DMA_DEV_TO_MEM;
	config.src_addr = (phys_addr_t)(st->dma_st.phys_addr
			  + AT91_SAMA5D2_LCDR);
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	config.src_maxburst = 1;
	config.dst_maxburst = 1;

	if (dmaengine_slave_config(st->dma_st.dma_chan, &config)) {
		dev_info(&pdev->dev, "can't configure DMA slave\n");
		goto dma_free_area;
	}

	dev_info(&pdev->dev, "using %s for rx DMA transfers\n",
		 dma_chan_name(st->dma_st.dma_chan));

	return;

dma_free_area:
	dma_free_coherent(st->dma_st.dma_chan->device->dev, pages * PAGE_SIZE,
			  st->dma_st.rx_buf, st->dma_st.rx_dma_buf);
dma_chan_disable:
	dma_release_channel(st->dma_st.dma_chan);
	st->dma_st.dma_chan = 0;
dma_exit:
	dev_info(&pdev->dev, "continuing without DMA support\n");
}