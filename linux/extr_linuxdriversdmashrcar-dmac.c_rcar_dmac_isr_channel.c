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
typedef  int u32 ;
struct TYPE_3__ {TYPE_2__* device; } ;
struct rcar_dmac_chan {int index; TYPE_1__ chan; int /*<<< orphan*/  lock; } ;
struct rcar_dmac {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RCAR_DMACHCLR ; 
 int /*<<< orphan*/  RCAR_DMACHCR ; 
 int RCAR_DMACHCR_CAE ; 
 int RCAR_DMACHCR_DE ; 
 int RCAR_DMACHCR_DSE ; 
 int RCAR_DMACHCR_TE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int rcar_dmac_chan_read (struct rcar_dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_dmac_chan_reinit (struct rcar_dmac_chan*) ; 
 int /*<<< orphan*/  rcar_dmac_chan_write (struct rcar_dmac_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcar_dmac_chcr_de_barrier (struct rcar_dmac_chan*) ; 
 int /*<<< orphan*/  rcar_dmac_isr_desc_stage_end (struct rcar_dmac_chan*) ; 
 int /*<<< orphan*/  rcar_dmac_isr_transfer_end (struct rcar_dmac_chan*) ; 
 int /*<<< orphan*/  rcar_dmac_write (struct rcar_dmac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct rcar_dmac* to_rcar_dmac (TYPE_2__*) ; 

__attribute__((used)) static irqreturn_t rcar_dmac_isr_channel(int irq, void *dev)
{
	u32 mask = RCAR_DMACHCR_DSE | RCAR_DMACHCR_TE;
	struct rcar_dmac_chan *chan = dev;
	irqreturn_t ret = IRQ_NONE;
	bool reinit = false;
	u32 chcr;

	spin_lock(&chan->lock);

	chcr = rcar_dmac_chan_read(chan, RCAR_DMACHCR);
	if (chcr & RCAR_DMACHCR_CAE) {
		struct rcar_dmac *dmac = to_rcar_dmac(chan->chan.device);

		/*
		 * We don't need to call rcar_dmac_chan_halt()
		 * because channel is already stopped in error case.
		 * We need to clear register and check DE bit as recovery.
		 */
		rcar_dmac_write(dmac, RCAR_DMACHCLR, 1 << chan->index);
		rcar_dmac_chcr_de_barrier(chan);
		reinit = true;
		goto spin_lock_end;
	}

	if (chcr & RCAR_DMACHCR_TE)
		mask |= RCAR_DMACHCR_DE;
	rcar_dmac_chan_write(chan, RCAR_DMACHCR, chcr & ~mask);
	if (mask & RCAR_DMACHCR_DE)
		rcar_dmac_chcr_de_barrier(chan);

	if (chcr & RCAR_DMACHCR_DSE)
		ret |= rcar_dmac_isr_desc_stage_end(chan);

	if (chcr & RCAR_DMACHCR_TE)
		ret |= rcar_dmac_isr_transfer_end(chan);

spin_lock_end:
	spin_unlock(&chan->lock);

	if (reinit) {
		dev_err(chan->chan.device->dev, "Channel Address Error\n");

		rcar_dmac_chan_reinit(chan);
		ret = IRQ_HANDLED;
	}

	return ret;
}