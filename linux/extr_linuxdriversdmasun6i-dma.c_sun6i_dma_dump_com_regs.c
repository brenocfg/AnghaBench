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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct sun6i_dma_dev {scalar_t__ base; TYPE_1__ slave; } ;

/* Variables and functions */
 scalar_t__ DMA_IRQ_EN (int) ; 
 scalar_t__ DMA_IRQ_STAT (int) ; 
 scalar_t__ DMA_STAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline void sun6i_dma_dump_com_regs(struct sun6i_dma_dev *sdev)
{
	dev_dbg(sdev->slave.dev, "Common register:\n"
		"\tmask0(%04x): 0x%08x\n"
		"\tmask1(%04x): 0x%08x\n"
		"\tpend0(%04x): 0x%08x\n"
		"\tpend1(%04x): 0x%08x\n"
		"\tstats(%04x): 0x%08x\n",
		DMA_IRQ_EN(0), readl(sdev->base + DMA_IRQ_EN(0)),
		DMA_IRQ_EN(1), readl(sdev->base + DMA_IRQ_EN(1)),
		DMA_IRQ_STAT(0), readl(sdev->base + DMA_IRQ_STAT(0)),
		DMA_IRQ_STAT(1), readl(sdev->base + DMA_IRQ_STAT(1)),
		DMA_STAT, readl(sdev->base + DMA_STAT));
}