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
typedef  int /*<<< orphan*/  u32 ;
struct gsc_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ GSC_IRQ ; 
 int GSC_IRQ_DONE ; 
 int GSC_IRQ_OVERRUN ; 
 int /*<<< orphan*/  GSC_IRQ_STATUS_FRM_DONE_IRQ ; 
 int /*<<< orphan*/  GSC_IRQ_STATUS_OR_IRQ ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void gsc_hw_clear_irq(struct gsc_dev *dev, int irq)
{
	u32 cfg = readl(dev->regs + GSC_IRQ);
	if (irq == GSC_IRQ_OVERRUN)
		cfg |= GSC_IRQ_STATUS_OR_IRQ;
	else if (irq == GSC_IRQ_DONE)
		cfg |= GSC_IRQ_STATUS_FRM_DONE_IRQ;
	writel(cfg, dev->regs + GSC_IRQ);
}