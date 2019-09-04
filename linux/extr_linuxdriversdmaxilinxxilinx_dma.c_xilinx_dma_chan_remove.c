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
struct xilinx_dma_chan {scalar_t__ irq; TYPE_1__ common; int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  XILINX_DMA_DMAXR_ALL_IRQ_MASK ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMACR ; 
 int /*<<< orphan*/  dma_ctrl_clr (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct xilinx_dma_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xilinx_dma_chan_remove(struct xilinx_dma_chan *chan)
{
	/* Disable all interrupts */
	dma_ctrl_clr(chan, XILINX_DMA_REG_DMACR,
		      XILINX_DMA_DMAXR_ALL_IRQ_MASK);

	if (chan->irq > 0)
		free_irq(chan->irq, chan);

	tasklet_kill(&chan->tasklet);

	list_del(&chan->common.device_node);
}