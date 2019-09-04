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
struct TYPE_4__ {int /*<<< orphan*/  device_node; } ;
struct zynqmp_dma_chan {TYPE_2__ common; int /*<<< orphan*/  tasklet; scalar_t__ irq; TYPE_1__* zdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,scalar_t__,struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zynqmp_dma_chan_remove(struct zynqmp_dma_chan *chan)
{
	if (!chan)
		return;

	if (chan->irq)
		devm_free_irq(chan->zdev->dev, chan->irq, chan);
	tasklet_kill(&chan->tasklet);
	list_del(&chan->common.device_node);
}