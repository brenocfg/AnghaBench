#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct omap_chan {int paused; int cyclic; TYPE_2__ vc; TYPE_1__* desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  omap_dma_stop (struct omap_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct omap_chan* to_omap_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_terminate_vdesc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_dma_terminate_all(struct dma_chan *chan)
{
	struct omap_chan *c = to_omap_dma_chan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&c->vc.lock, flags);

	/*
	 * Stop DMA activity: we assume the callback will not be called
	 * after omap_dma_stop() returns (even if it does, it will see
	 * c->desc is NULL and exit.)
	 */
	if (c->desc) {
		vchan_terminate_vdesc(&c->desc->vd);
		c->desc = NULL;
		/* Avoid stopping the dma twice */
		if (!c->paused)
			omap_dma_stop(c);
	}

	c->cyclic = false;
	c->paused = false;

	vchan_get_all_descriptors(&c->vc, &head);
	spin_unlock_irqrestore(&c->vc.lock, flags);
	vchan_dma_desc_free_list(&c->vc, &head);

	return 0;
}