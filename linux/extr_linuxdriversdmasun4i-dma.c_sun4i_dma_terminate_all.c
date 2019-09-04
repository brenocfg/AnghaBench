#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct sun4i_dma_vchan {TYPE_1__ vc; struct sun4i_dma_pchan* pchan; int /*<<< orphan*/ * processing; } ;
struct sun4i_dma_pchan {scalar_t__ base; scalar_t__ is_dedicated; } ;
struct sun4i_dma_dev {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ SUN4I_DDMA_CFG_REG ; 
 scalar_t__ SUN4I_NDMA_CFG_REG ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  release_pchan (struct sun4i_dma_dev*,struct sun4i_dma_pchan*) ; 
 int /*<<< orphan*/  set_pchan_interrupt (struct sun4i_dma_dev*,struct sun4i_dma_pchan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sun4i_dma_dev* to_sun4i_dma_dev (int /*<<< orphan*/ ) ; 
 struct sun4i_dma_vchan* to_sun4i_dma_vchan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun4i_dma_terminate_all(struct dma_chan *chan)
{
	struct sun4i_dma_dev *priv = to_sun4i_dma_dev(chan->device);
	struct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	struct sun4i_dma_pchan *pchan = vchan->pchan;
	LIST_HEAD(head);
	unsigned long flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);
	vchan_get_all_descriptors(&vchan->vc, &head);
	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	/*
	 * Clearing the configuration register will halt the pchan. Interrupts
	 * may still trigger, so don't forget to disable them.
	 */
	if (pchan) {
		if (pchan->is_dedicated)
			writel(0, pchan->base + SUN4I_DDMA_CFG_REG);
		else
			writel(0, pchan->base + SUN4I_NDMA_CFG_REG);
		set_pchan_interrupt(priv, pchan, 0, 0);
		release_pchan(priv, pchan);
	}

	spin_lock_irqsave(&vchan->vc.lock, flags);
	vchan_dma_desc_free_list(&vchan->vc, &head);
	/* Clear these so the vchan is usable again */
	vchan->processing = NULL;
	vchan->pchan = NULL;
	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	return 0;
}