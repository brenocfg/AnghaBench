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
struct shdma_ops {scalar_t__ (* chan_irq ) (struct shdma_chan*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct shdma_chan {int /*<<< orphan*/  chan_lock; TYPE_1__ dma_chan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {struct shdma_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct shdma_chan*,int) ; 
 TYPE_2__* to_shdma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t chan_irq(int irq, void *dev)
{
	struct shdma_chan *schan = dev;
	const struct shdma_ops *ops =
		to_shdma_dev(schan->dma_chan.device)->ops;
	irqreturn_t ret;

	spin_lock(&schan->chan_lock);

	ret = ops->chan_irq(schan, irq) ? IRQ_WAKE_THREAD : IRQ_NONE;

	spin_unlock(&schan->chan_lock);

	return ret;
}