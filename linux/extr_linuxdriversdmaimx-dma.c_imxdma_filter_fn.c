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
struct imxdma_filter_data {int /*<<< orphan*/  request; TYPE_2__* imxdma; } ;
struct imxdma_channel {int /*<<< orphan*/  dma_request; } ;
struct dma_chan {int /*<<< orphan*/ * private; TYPE_1__* device; } ;
struct TYPE_4__ {scalar_t__ dev; } ;
struct TYPE_3__ {scalar_t__ dev; } ;

/* Variables and functions */
 struct imxdma_channel* to_imxdma_chan (struct dma_chan*) ; 

__attribute__((used)) static bool imxdma_filter_fn(struct dma_chan *chan, void *param)
{
	struct imxdma_filter_data *fdata = param;
	struct imxdma_channel *imxdma_chan = to_imxdma_chan(chan);

	if (chan->device->dev != fdata->imxdma->dev)
		return false;

	imxdma_chan->dma_request = fdata->request;
	chan->private = NULL;

	return true;
}