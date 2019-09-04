#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dma_chan {int dummy; } ;
struct bcm2835_dmadev {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_1__ chan; } ;
struct bcm2835_chan {TYPE_3__ vc; TYPE_2__* desc; int /*<<< orphan*/  node; } ;
struct TYPE_6__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_dma_abort (struct bcm2835_chan*) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct bcm2835_chan* to_bcm2835_dma_chan (struct dma_chan*) ; 
 struct bcm2835_dmadev* to_bcm2835_dma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_terminate_vdesc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_dma_terminate_all(struct dma_chan *chan)
{
	struct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	struct bcm2835_dmadev *d = to_bcm2835_dma_dev(c->vc.chan.device);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&c->vc.lock, flags);

	/* Prevent this channel being scheduled */
	spin_lock(&d->lock);
	list_del_init(&c->node);
	spin_unlock(&d->lock);

	/* stop DMA activity */
	if (c->desc) {
		vchan_terminate_vdesc(&c->desc->vd);
		c->desc = NULL;
		bcm2835_dma_abort(c);
	}

	vchan_get_all_descriptors(&c->vc, &head);
	spin_unlock_irqrestore(&c->vc.lock, flags);
	vchan_dma_desc_free_list(&c->vc, &head);

	return 0;
}