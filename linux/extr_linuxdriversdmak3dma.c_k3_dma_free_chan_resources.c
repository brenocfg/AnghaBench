#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct k3_dma_dev {int /*<<< orphan*/  lock; } ;
struct k3_dma_chan {scalar_t__ ccfg; int /*<<< orphan*/  vc; int /*<<< orphan*/  node; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct k3_dma_chan* to_k3_chan (struct dma_chan*) ; 
 struct k3_dma_dev* to_k3_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void k3_dma_free_chan_resources(struct dma_chan *chan)
{
	struct k3_dma_chan *c = to_k3_chan(chan);
	struct k3_dma_dev *d = to_k3_dma(chan->device);
	unsigned long flags;

	spin_lock_irqsave(&d->lock, flags);
	list_del_init(&c->node);
	spin_unlock_irqrestore(&d->lock, flags);

	vchan_free_chan_resources(&c->vc);
	c->ccfg = 0;
}