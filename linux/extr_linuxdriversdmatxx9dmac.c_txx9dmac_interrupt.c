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
struct txx9dmac_dev {int /*<<< orphan*/  tasklet; TYPE_2__** chan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MCR ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  dma_readl (struct txx9dmac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t txx9dmac_interrupt(int irq, void *dev_id)
{
	struct txx9dmac_dev *ddev = dev_id;

	dev_vdbg(ddev->chan[0]->dma.dev, "interrupt: status=%#x\n",
			dma_readl(ddev, MCR));

	tasklet_schedule(&ddev->tasklet);
	/*
	 * Just disable the interrupts. We'll turn them back on in the
	 * softirq handler.
	 */
	disable_irq_nosync(irq);

	return IRQ_HANDLED;
}