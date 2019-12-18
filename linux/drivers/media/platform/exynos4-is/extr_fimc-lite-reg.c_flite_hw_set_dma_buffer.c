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
typedef  int /*<<< orphan*/  u32 ;
struct flite_buffer {unsigned int index; int /*<<< orphan*/  paddr; } ;
struct fimc_lite {scalar_t__ regs; TYPE_1__* dd; } ;
struct TYPE_2__ {int max_dma_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 scalar_t__ FLITE_REG_CIFCNTSEQ ; 
 scalar_t__ FLITE_REG_CIOSA ; 
 scalar_t__ FLITE_REG_CIOSAN (unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void flite_hw_set_dma_buffer(struct fimc_lite *dev, struct flite_buffer *buf)
{
	unsigned int index;
	u32 cfg;

	if (dev->dd->max_dma_bufs == 1)
		index = 0;
	else
		index = buf->index;

	if (index == 0)
		writel(buf->paddr, dev->regs + FLITE_REG_CIOSA);
	else
		writel(buf->paddr, dev->regs + FLITE_REG_CIOSAN(index - 1));

	cfg = readl(dev->regs + FLITE_REG_CIFCNTSEQ);
	cfg |= BIT(index);
	writel(cfg, dev->regs + FLITE_REG_CIFCNTSEQ);
}