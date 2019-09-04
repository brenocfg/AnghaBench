#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct k3_dma_phy {int /*<<< orphan*/ * ds_done; TYPE_2__* ds_run; int /*<<< orphan*/ * vchan; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct k3_dma_dev {int /*<<< orphan*/  lock; TYPE_1__ slave; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct k3_dma_chan {TYPE_3__ vc; struct k3_dma_phy* phy; int /*<<< orphan*/  node; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_7__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  k3_dma_terminate_chan (struct k3_dma_phy*,struct k3_dma_dev*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct k3_dma_chan* to_k3_chan (struct dma_chan*) ; 
 struct k3_dma_dev* to_k3_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_terminate_vdesc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int k3_dma_terminate_all(struct dma_chan *chan)
{
	struct k3_dma_chan *c = to_k3_chan(chan);
	struct k3_dma_dev *d = to_k3_dma(chan->device);
	struct k3_dma_phy *p = c->phy;
	unsigned long flags;
	LIST_HEAD(head);

	dev_dbg(d->slave.dev, "vchan %p: terminate all\n", &c->vc);

	/* Prevent this channel being scheduled */
	spin_lock(&d->lock);
	list_del_init(&c->node);
	spin_unlock(&d->lock);

	/* Clear the tx descriptor lists */
	spin_lock_irqsave(&c->vc.lock, flags);
	vchan_get_all_descriptors(&c->vc, &head);
	if (p) {
		/* vchan is assigned to a pchan - stop the channel */
		k3_dma_terminate_chan(p, d);
		c->phy = NULL;
		p->vchan = NULL;
		if (p->ds_run) {
			vchan_terminate_vdesc(&p->ds_run->vd);
			p->ds_run = NULL;
		}
		p->ds_done = NULL;
	}
	spin_unlock_irqrestore(&c->vc.lock, flags);
	vchan_dma_desc_free_list(&c->vc, &head);

	return 0;
}