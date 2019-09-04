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
struct pl08x_dma_chan {int /*<<< orphan*/  name; } ;
struct dma_chan {TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  drv; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 TYPE_3__ pl08x_amba_driver ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 struct pl08x_dma_chan* to_pl08x_chan (struct dma_chan*) ; 

bool pl08x_filter_id(struct dma_chan *chan, void *chan_id)
{
	struct pl08x_dma_chan *plchan;
	char *name = chan_id;

	/* Reject channels for devices not bound to this driver */
	if (chan->device->dev->driver != &pl08x_amba_driver.drv)
		return false;

	plchan = to_pl08x_chan(chan);

	/* Check that the channel is not taken! */
	if (!strcmp(plchan->name, name))
		return true;

	return false;
}