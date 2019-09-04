#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct of_phandle_args {int args_count; int* args; } ;
struct of_dma {int /*<<< orphan*/  of_node; struct jz4780_dma_dev* of_dma_data; } ;
struct jz4780_dma_filter_data {int transfer_type; int channel; int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  cap_mask; } ;
struct jz4780_dma_dev {int chan_reserved; TYPE_3__* chan; TYPE_1__ dma_device; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_5__ {int /*<<< orphan*/  chan; } ;
struct TYPE_6__ {int transfer_type; TYPE_2__ vchan; } ;

/* Variables and functions */
 int BIT (int) ; 
 int JZ_DMA_NR_CHANNELS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct dma_chan* dma_get_slave_channel (int /*<<< orphan*/ *) ; 
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jz4780_dma_filter_data*) ; 
 int /*<<< orphan*/  jz4780_dma_filter_fn ; 

__attribute__((used)) static struct dma_chan *jz4780_of_dma_xlate(struct of_phandle_args *dma_spec,
	struct of_dma *ofdma)
{
	struct jz4780_dma_dev *jzdma = ofdma->of_dma_data;
	dma_cap_mask_t mask = jzdma->dma_device.cap_mask;
	struct jz4780_dma_filter_data data;

	if (dma_spec->args_count != 2)
		return NULL;

	data.of_node = ofdma->of_node;
	data.transfer_type = dma_spec->args[0];
	data.channel = dma_spec->args[1];

	if (data.channel > -1) {
		if (data.channel >= JZ_DMA_NR_CHANNELS) {
			dev_err(jzdma->dma_device.dev,
				"device requested non-existent channel %u\n",
				data.channel);
			return NULL;
		}

		/* Can only select a channel marked as reserved. */
		if (!(jzdma->chan_reserved & BIT(data.channel))) {
			dev_err(jzdma->dma_device.dev,
				"device requested unreserved channel %u\n",
				data.channel);
			return NULL;
		}

		jzdma->chan[data.channel].transfer_type = data.transfer_type;

		return dma_get_slave_channel(
			&jzdma->chan[data.channel].vchan.chan);
	} else {
		return dma_request_channel(mask, jz4780_dma_filter_fn, &data);
	}
}