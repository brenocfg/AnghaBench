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
typedef  int u32 ;
struct timb_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int chancnt; } ;
struct timb_dma {scalar_t__ membase; struct timb_dma_chan* channels; TYPE_1__ dma; } ;

/* Variables and functions */
 scalar_t__ TIMBDMA_IER ; 
 scalar_t__ TIMBDMA_ISR ; 
 int /*<<< orphan*/  __td_finish (struct timb_dma_chan*) ; 
 int __td_ier_mask (struct timb_dma*) ; 
 int /*<<< orphan*/  __td_start_next (struct timb_dma_chan*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void td_tasklet(unsigned long data)
{
	struct timb_dma *td = (struct timb_dma *)data;
	u32 isr;
	u32 ipr;
	u32 ier;
	int i;

	isr = ioread32(td->membase + TIMBDMA_ISR);
	ipr = isr & __td_ier_mask(td);

	/* ack the interrupts */
	iowrite32(ipr, td->membase + TIMBDMA_ISR);

	for (i = 0; i < td->dma.chancnt; i++)
		if (ipr & (1 << i)) {
			struct timb_dma_chan *td_chan = td->channels + i;
			spin_lock(&td_chan->lock);
			__td_finish(td_chan);
			if (!list_empty(&td_chan->queue))
				__td_start_next(td_chan);
			spin_unlock(&td_chan->lock);
		}

	ier = __td_ier_mask(td);
	iowrite32(ier, td->membase + TIMBDMA_IER);
}