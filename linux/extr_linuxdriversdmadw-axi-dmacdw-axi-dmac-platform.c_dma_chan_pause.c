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
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct axi_dma_chan {int is_paused; TYPE_1__ vc; int /*<<< orphan*/  chip; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DMAC_CHAN_SUSP_SHIFT ; 
 int DMAC_CHAN_SUSP_WE_SHIFT ; 
 int /*<<< orphan*/  DMAC_CHEN ; 
 int DWAXIDMAC_IRQ_SUSPENDED ; 
 int EAGAIN ; 
 int /*<<< orphan*/  axi_chan_irq_clear (struct axi_dma_chan*,int) ; 
 int axi_chan_irq_read (struct axi_dma_chan*) ; 
 int axi_dma_ioread32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_dma_iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct axi_dma_chan* dchan_to_axi_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dma_chan_pause(struct dma_chan *dchan)
{
	struct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	unsigned long flags;
	unsigned int timeout = 20; /* timeout iterations */
	u32 val;

	spin_lock_irqsave(&chan->vc.lock, flags);

	val = axi_dma_ioread32(chan->chip, DMAC_CHEN);
	val |= BIT(chan->id) << DMAC_CHAN_SUSP_SHIFT |
	       BIT(chan->id) << DMAC_CHAN_SUSP_WE_SHIFT;
	axi_dma_iowrite32(chan->chip, DMAC_CHEN, val);

	do  {
		if (axi_chan_irq_read(chan) & DWAXIDMAC_IRQ_SUSPENDED)
			break;

		udelay(2);
	} while (--timeout);

	axi_chan_irq_clear(chan, DWAXIDMAC_IRQ_SUSPENDED);

	chan->is_paused = true;

	spin_unlock_irqrestore(&chan->vc.lock, flags);

	return timeout ? 0 : -EAGAIN;
}