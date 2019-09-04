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
struct dma_chan {unsigned int chan_id; TYPE_1__* device; } ;
struct TYPE_2__ {unsigned int dev_id; } ;

/* Variables and functions */
 unsigned int SIRFSOC_DMA_CHANNELS ; 

bool sirfsoc_dma_filter_id(struct dma_chan *chan, void *chan_id)
{
	unsigned int ch_nr = (unsigned int) chan_id;

	if (ch_nr == chan->chan_id +
		chan->device->dev_id * SIRFSOC_DMA_CHANNELS)
		return true;

	return false;
}