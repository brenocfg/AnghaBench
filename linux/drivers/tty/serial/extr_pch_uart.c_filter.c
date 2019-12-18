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
struct pch_dma_slave {scalar_t__ chan_id; scalar_t__ dma_dev; } ;
struct dma_chan {scalar_t__ chan_id; struct pch_dma_slave* private; TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */

__attribute__((used)) static bool filter(struct dma_chan *chan, void *slave)
{
	struct pch_dma_slave *param = slave;

	if ((chan->chan_id == param->chan_id) && (param->dma_dev ==
						  chan->device->dev)) {
		chan->private = param;
		return true;
	} else {
		return false;
	}
}