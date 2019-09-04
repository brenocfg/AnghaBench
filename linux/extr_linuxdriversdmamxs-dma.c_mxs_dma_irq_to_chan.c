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
struct mxs_dma_engine {int nr_channels; TYPE_1__* mxs_chans; } ;
struct TYPE_2__ {int chan_irq; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mxs_dma_irq_to_chan(struct mxs_dma_engine *mxs_dma, int irq)
{
	int i;

	for (i = 0; i != mxs_dma->nr_channels; ++i)
		if (mxs_dma->mxs_chans[i].chan_irq == irq)
			return i;

	return -EINVAL;
}