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
struct zynqmp_dma_chan {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ZYNQMP_DMA_IDS ; 
 int /*<<< orphan*/  ZYNQMP_DMA_IDS_DEFAULT_MASK ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zynqmp_dma_chan_desc_cleanup (struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  zynqmp_dma_complete_descriptor (struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  zynqmp_dma_free_descriptors (struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  zynqmp_dma_init (struct zynqmp_dma_chan*) ; 

__attribute__((used)) static void zynqmp_dma_reset(struct zynqmp_dma_chan *chan)
{
	writel(ZYNQMP_DMA_IDS_DEFAULT_MASK, chan->regs + ZYNQMP_DMA_IDS);

	zynqmp_dma_complete_descriptor(chan);
	zynqmp_dma_chan_desc_cleanup(chan);
	zynqmp_dma_free_descriptors(chan);
	zynqmp_dma_init(chan);
}