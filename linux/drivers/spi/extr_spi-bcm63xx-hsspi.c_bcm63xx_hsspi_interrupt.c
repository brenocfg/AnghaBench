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
struct bcm63xx_hsspi {int /*<<< orphan*/  done; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSSPI_INT_CLEAR_ALL ; 
 scalar_t__ HSSPI_INT_MASK_REG ; 
 scalar_t__ HSSPI_INT_STATUS_MASKED_REG ; 
 scalar_t__ HSSPI_INT_STATUS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bcm63xx_hsspi_interrupt(int irq, void *dev_id)
{
	struct bcm63xx_hsspi *bs = (struct bcm63xx_hsspi *)dev_id;

	if (__raw_readl(bs->regs + HSSPI_INT_STATUS_MASKED_REG) == 0)
		return IRQ_NONE;

	__raw_writel(HSSPI_INT_CLEAR_ALL, bs->regs + HSSPI_INT_STATUS_REG);
	__raw_writel(0, bs->regs + HSSPI_INT_MASK_REG);

	complete(&bs->done);

	return IRQ_HANDLED;
}