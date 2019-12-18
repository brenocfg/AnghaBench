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
struct gdma_dmaengine_chan {int /*<<< orphan*/  id; scalar_t__ desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct gdma_dma_dev {int /*<<< orphan*/  chan_issued; TYPE_2__ ddev; int /*<<< orphan*/  cnt; struct gdma_dmaengine_chan* chan; TYPE_1__* data; } ;
struct TYPE_3__ {int chancnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdma_start_transfer (struct gdma_dma_dev*,struct gdma_dmaengine_chan*) ; 
 scalar_t__ test_and_clear_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gdma_dma_tasklet(unsigned long arg)
{
	struct gdma_dma_dev *dma_dev = (struct gdma_dma_dev *)arg;
	struct gdma_dmaengine_chan *chan;
	static unsigned int last_chan;
	unsigned int i, chan_mask;

	/* record last chan to round robin all chans */
	i = last_chan;
	chan_mask = dma_dev->data->chancnt - 1;
	do {
		/*
		 * on mt7621. when verify with dmatest with all
		 * channel is enable. we need to limit only two
		 * channel is working at the same time. otherwise the
		 * data will have problem.
		 */
		if (atomic_read(&dma_dev->cnt) >= 2) {
			last_chan = i;
			break;
		}

		if (test_and_clear_bit(i, &dma_dev->chan_issued)) {
			chan = &dma_dev->chan[i];
			if (chan->desc) {
				atomic_inc(&dma_dev->cnt);
				gdma_start_transfer(dma_dev, chan);
			} else {
				dev_dbg(dma_dev->ddev.dev,
					"chan %d no desc to issue\n",
					chan->id);
			}
			if (!dma_dev->chan_issued)
				break;
		}

		i = (i + 1) & chan_mask;
	} while (i != last_chan);
}