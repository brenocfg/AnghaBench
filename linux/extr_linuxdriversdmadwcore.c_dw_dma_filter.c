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
struct dw_dma_slave {scalar_t__ dma_dev; } ;
struct dw_dma_chan {int /*<<< orphan*/  dws; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dw_dma_slave*,int) ; 
 struct dw_dma_chan* to_dw_dma_chan (struct dma_chan*) ; 

bool dw_dma_filter(struct dma_chan *chan, void *param)
{
	struct dw_dma_chan *dwc = to_dw_dma_chan(chan);
	struct dw_dma_slave *dws = param;

	if (dws->dma_dev != chan->device->dev)
		return false;

	/* We have to copy data since dws can be temporary storage */
	memcpy(&dwc->dws, dws, sizeof(struct dw_dma_slave));

	return true;
}