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
struct k3_dma_phy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct k3_dma_dev {int /*<<< orphan*/  lock; TYPE_1__ slave; } ;
struct k3_dma_chan {scalar_t__ status; int /*<<< orphan*/  node; int /*<<< orphan*/  vc; struct k3_dma_phy* phy; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ DMA_IN_PROGRESS ; 
 scalar_t__ DMA_PAUSED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k3_dma_pause_dma (struct k3_dma_phy*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct k3_dma_chan* to_k3_chan (struct dma_chan*) ; 
 struct k3_dma_dev* to_k3_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int k3_dma_transfer_pause(struct dma_chan *chan)
{
	struct k3_dma_chan *c = to_k3_chan(chan);
	struct k3_dma_dev *d = to_k3_dma(chan->device);
	struct k3_dma_phy *p = c->phy;

	dev_dbg(d->slave.dev, "vchan %p: pause\n", &c->vc);
	if (c->status == DMA_IN_PROGRESS) {
		c->status = DMA_PAUSED;
		if (p) {
			k3_dma_pause_dma(p, false);
		} else {
			spin_lock(&d->lock);
			list_del_init(&c->node);
			spin_unlock(&d->lock);
		}
	}

	return 0;
}