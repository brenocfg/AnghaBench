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
typedef  int u32 ;
struct irq_data {scalar_t__ chip_data; } ;
struct grpci1_priv {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ IRQ_MASK_BIT ; 
 int REGLOAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGSTORE (int /*<<< orphan*/ ,int) ; 
 struct grpci1_priv* grpci1priv ; 

__attribute__((used)) static void grpci1_unmask_irq(struct irq_data *data)
{
	u32 irqidx;
	struct grpci1_priv *priv = grpci1priv;

	irqidx = (u32)data->chip_data - 1;
	if (irqidx > 3) /* only unmask PCI interrupts here */
		return;
	irqidx += IRQ_MASK_BIT;

	REGSTORE(priv->regs->irq, REGLOAD(priv->regs->irq) | (1 << irqidx));
}