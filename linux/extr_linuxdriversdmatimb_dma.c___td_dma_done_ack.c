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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int chan_id; } ;
struct timb_dma_chan {TYPE_1__ chan; } ;
struct timb_dma {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ TIMBDMA_ISR ; 
 int /*<<< orphan*/  chan2dev (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,struct timb_dma*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static bool __td_dma_done_ack(struct timb_dma_chan *td_chan)
{
	int id = td_chan->chan.chan_id;
	struct timb_dma *td = (struct timb_dma *)((u8 *)td_chan -
		id * sizeof(struct timb_dma_chan) - sizeof(struct timb_dma));
	u32 isr;
	bool done = false;

	dev_dbg(chan2dev(&td_chan->chan), "Checking irq: %d, td: %p\n", id, td);

	isr = ioread32(td->membase + TIMBDMA_ISR) & (1 << id);
	if (isr) {
		iowrite32(isr, td->membase + TIMBDMA_ISR);
		done = true;
	}

	return done;
}