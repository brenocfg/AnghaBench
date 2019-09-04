#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device* dev; } ;
struct stm32_dma_device {struct stm32_dma_chan* chan; TYPE_1__ ddev; } ;
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct stm32_dma_chan {TYPE_2__ vchan; } ;
struct stm32_dma_cfg {size_t channel_id; size_t request_line; size_t stream_config; size_t features; } ;
struct of_phandle_args {int args_count; size_t* args; } ;
struct of_dma {struct stm32_dma_device* of_dma_data; } ;
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t STM32_DMA_MAX_CHANNELS ; 
 scalar_t__ STM32_DMA_MAX_REQUEST_ID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct dma_chan* dma_get_slave_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_dma_set_config (struct stm32_dma_chan*,struct stm32_dma_cfg*) ; 

__attribute__((used)) static struct dma_chan *stm32_dma_of_xlate(struct of_phandle_args *dma_spec,
					   struct of_dma *ofdma)
{
	struct stm32_dma_device *dmadev = ofdma->of_dma_data;
	struct device *dev = dmadev->ddev.dev;
	struct stm32_dma_cfg cfg;
	struct stm32_dma_chan *chan;
	struct dma_chan *c;

	if (dma_spec->args_count < 4) {
		dev_err(dev, "Bad number of cells\n");
		return NULL;
	}

	cfg.channel_id = dma_spec->args[0];
	cfg.request_line = dma_spec->args[1];
	cfg.stream_config = dma_spec->args[2];
	cfg.features = dma_spec->args[3];

	if (cfg.channel_id >= STM32_DMA_MAX_CHANNELS ||
	    cfg.request_line >= STM32_DMA_MAX_REQUEST_ID) {
		dev_err(dev, "Bad channel and/or request id\n");
		return NULL;
	}

	chan = &dmadev->chan[cfg.channel_id];

	c = dma_get_slave_channel(&chan->vchan.chan);
	if (!c) {
		dev_err(dev, "No more channels available\n");
		return NULL;
	}

	stm32_dma_set_config(chan, &cfg);

	return c;
}