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
struct zynqmp_dma_chan {int idle; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ZYNQMP_DMA_CTRL2 ; 
 int /*<<< orphan*/  ZYNQMP_DMA_ENABLE ; 
 scalar_t__ ZYNQMP_DMA_IER ; 
 int /*<<< orphan*/  ZYNQMP_DMA_INT_EN_DEFAULT_MASK ; 
 scalar_t__ ZYNQMP_DMA_TOTAL_BYTE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void zynqmp_dma_start(struct zynqmp_dma_chan *chan)
{
	writel(ZYNQMP_DMA_INT_EN_DEFAULT_MASK, chan->regs + ZYNQMP_DMA_IER);
	writel(0, chan->regs + ZYNQMP_DMA_TOTAL_BYTE);
	chan->idle = false;
	writel(ZYNQMP_DMA_ENABLE, chan->regs + ZYNQMP_DMA_CTRL2);
}