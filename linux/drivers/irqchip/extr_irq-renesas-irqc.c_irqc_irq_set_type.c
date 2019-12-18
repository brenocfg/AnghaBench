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
struct irqc_priv {scalar_t__ iomem; int /*<<< orphan*/ * irq; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IRQC_CONFIG (int) ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct irqc_priv* irq_data_to_priv (struct irq_data*) ; 
 int /*<<< orphan*/  irqc_dbg (int /*<<< orphan*/ *,char*) ; 
 unsigned char* irqc_sense ; 
 int irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static int irqc_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct irqc_priv *p = irq_data_to_priv(d);
	int hw_irq = irqd_to_hwirq(d);
	unsigned char value = irqc_sense[type & IRQ_TYPE_SENSE_MASK];
	u32 tmp;

	irqc_dbg(&p->irq[hw_irq], "sense");

	if (!value)
		return -EINVAL;

	tmp = ioread32(p->iomem + IRQC_CONFIG(hw_irq));
	tmp &= ~0x3f;
	tmp |= value;
	iowrite32(tmp, p->iomem + IRQC_CONFIG(hw_irq));
	return 0;
}