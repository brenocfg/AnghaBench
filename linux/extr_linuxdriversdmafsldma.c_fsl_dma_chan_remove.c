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
struct TYPE_2__ {int /*<<< orphan*/  device_node; } ;
struct fsldma_chan {int /*<<< orphan*/  regs; TYPE_1__ common; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fsldma_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_dma_chan_remove(struct fsldma_chan *chan)
{
	irq_dispose_mapping(chan->irq);
	list_del(&chan->common.device_node);
	iounmap(chan->regs);
	kfree(chan);
}