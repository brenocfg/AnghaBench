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
struct knav_dma_chan {TYPE_1__* dma; int /*<<< orphan*/  flow; int /*<<< orphan*/  channel; int /*<<< orphan*/  ref_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chan_stop (struct knav_dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* kdev ; 
 int /*<<< orphan*/  knav_dma_hw_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void knav_dma_close_channel(void *channel)
{
	struct knav_dma_chan *chan = channel;

	if (!kdev) {
		pr_err("keystone-navigator-dma driver not registered\n");
		return;
	}

	if (atomic_dec_return(&chan->ref_count) <= 0)
		chan_stop(chan);

	if (atomic_dec_return(&chan->dma->ref_count) <= 0)
		knav_dma_hw_destroy(chan->dma);

	dev_dbg(kdev->dev, "channel %d or flow %d closed from DMA %s\n",
			chan->channel, chan->flow, chan->dma->name);
}