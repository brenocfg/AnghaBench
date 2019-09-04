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
typedef  unsigned int u32 ;
struct mv_xor_v2_device {int /*<<< orphan*/  irq_tasklet; scalar_t__ dma_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MV_XOR_V2_DMA_DESQ_DONE_OFF ; 
 unsigned int MV_XOR_V2_DMA_DESQ_DONE_PENDING_MASK ; 
 unsigned int MV_XOR_V2_DMA_DESQ_DONE_PENDING_SHIFT ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mv_xor_v2_interrupt_handler(int irq, void *data)
{
	struct mv_xor_v2_device *xor_dev = data;
	unsigned int ndescs;
	u32 reg;

	reg = readl(xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_DONE_OFF);

	ndescs = ((reg >> MV_XOR_V2_DMA_DESQ_DONE_PENDING_SHIFT) &
		  MV_XOR_V2_DMA_DESQ_DONE_PENDING_MASK);

	/* No descriptors to process */
	if (!ndescs)
		return IRQ_NONE;

	/* schedule a tasklet to handle descriptors callbacks */
	tasklet_schedule(&xor_dev->irq_tasklet);

	return IRQ_HANDLED;
}