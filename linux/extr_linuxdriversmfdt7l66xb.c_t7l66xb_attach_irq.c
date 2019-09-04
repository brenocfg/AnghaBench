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
struct t7l66xb {unsigned int irq_base; int /*<<< orphan*/  irq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_EDGE_FALLING ; 
 unsigned int T7L66XB_NR_IRQS ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct t7l66xb*) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct t7l66xb*) ; 
 int /*<<< orphan*/  irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct t7l66xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  t7l66xb_chip ; 
 int /*<<< orphan*/  t7l66xb_irq ; 

__attribute__((used)) static void t7l66xb_attach_irq(struct platform_device *dev)
{
	struct t7l66xb *t7l66xb = platform_get_drvdata(dev);
	unsigned int irq, irq_base;

	irq_base = t7l66xb->irq_base;

	for (irq = irq_base; irq < irq_base + T7L66XB_NR_IRQS; irq++) {
		irq_set_chip_and_handler(irq, &t7l66xb_chip, handle_level_irq);
		irq_set_chip_data(irq, t7l66xb);
	}

	irq_set_irq_type(t7l66xb->irq, IRQ_TYPE_EDGE_FALLING);
	irq_set_chained_handler_and_data(t7l66xb->irq, t7l66xb_irq, t7l66xb);
}