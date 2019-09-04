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
typedef  int u32 ;
struct zynqmp_dma_chan {int idle; scalar_t__ regs; scalar_t__ is_dmacoherent; } ;

/* Variables and functions */
 int ZYNQMP_DMA_ARCACHE ; 
 int ZYNQMP_DMA_ARCACHE_OFST ; 
 int ZYNQMP_DMA_AWCACHE ; 
 int ZYNQMP_DMA_AWCACHE_OFST ; 
 int ZYNQMP_DMA_AXCACHE ; 
 int ZYNQMP_DMA_AXCACHE_OFST ; 
 int ZYNQMP_DMA_AXCACHE_VAL ; 
 int ZYNQMP_DMA_AXCOHRNT ; 
 scalar_t__ ZYNQMP_DMA_DATA_ATTR ; 
 scalar_t__ ZYNQMP_DMA_DSCR_ATTR ; 
 scalar_t__ ZYNQMP_DMA_IDS ; 
 int ZYNQMP_DMA_IDS_DEFAULT_MASK ; 
 scalar_t__ ZYNQMP_DMA_IRQ_DST_ACCT ; 
 scalar_t__ ZYNQMP_DMA_IRQ_SRC_ACCT ; 
 scalar_t__ ZYNQMP_DMA_ISR ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void zynqmp_dma_init(struct zynqmp_dma_chan *chan)
{
	u32 val;

	writel(ZYNQMP_DMA_IDS_DEFAULT_MASK, chan->regs + ZYNQMP_DMA_IDS);
	val = readl(chan->regs + ZYNQMP_DMA_ISR);
	writel(val, chan->regs + ZYNQMP_DMA_ISR);

	if (chan->is_dmacoherent) {
		val = ZYNQMP_DMA_AXCOHRNT;
		val = (val & ~ZYNQMP_DMA_AXCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAL << ZYNQMP_DMA_AXCACHE_OFST);
		writel(val, chan->regs + ZYNQMP_DMA_DSCR_ATTR);
	}

	val = readl(chan->regs + ZYNQMP_DMA_DATA_ATTR);
	if (chan->is_dmacoherent) {
		val = (val & ~ZYNQMP_DMA_ARCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAL << ZYNQMP_DMA_ARCACHE_OFST);
		val = (val & ~ZYNQMP_DMA_AWCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAL << ZYNQMP_DMA_AWCACHE_OFST);
	}
	writel(val, chan->regs + ZYNQMP_DMA_DATA_ATTR);

	/* Clearing the interrupt account rgisters */
	val = readl(chan->regs + ZYNQMP_DMA_IRQ_SRC_ACCT);
	val = readl(chan->regs + ZYNQMP_DMA_IRQ_DST_ACCT);

	chan->idle = true;
}