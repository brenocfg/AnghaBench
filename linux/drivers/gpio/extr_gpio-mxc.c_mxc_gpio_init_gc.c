#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxc_gpio_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  ack; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; } ;
struct irq_chip_type {TYPE_2__ regs; TYPE_1__ chip; } ;
struct irq_chip_generic {struct irq_chip_type* chip_types; struct mxc_gpio_port* private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GPIO_IMR ; 
 int /*<<< orphan*/  GPIO_ISR ; 
 int /*<<< orphan*/  IRQCHIP_MASK_ON_SUSPEND ; 
 int /*<<< orphan*/  IRQ_GC_INIT_NESTED_LOCK ; 
 int /*<<< orphan*/  IRQ_MSK (int) ; 
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 struct irq_chip_generic* devm_irq_alloc_generic_chip (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_irq_setup_generic_chip (int /*<<< orphan*/ ,struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_irq_type ; 
 int /*<<< orphan*/  gpio_set_wake_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_gc_ack_set_bit ; 
 int /*<<< orphan*/  irq_gc_mask_clr_bit ; 
 int /*<<< orphan*/  irq_gc_mask_set_bit ; 

__attribute__((used)) static int mxc_gpio_init_gc(struct mxc_gpio_port *port, int irq_base)
{
	struct irq_chip_generic *gc;
	struct irq_chip_type *ct;
	int rv;

	gc = devm_irq_alloc_generic_chip(port->dev, "gpio-mxc", 1, irq_base,
					 port->base, handle_level_irq);
	if (!gc)
		return -ENOMEM;
	gc->private = port;

	ct = gc->chip_types;
	ct->chip.irq_ack = irq_gc_ack_set_bit;
	ct->chip.irq_mask = irq_gc_mask_clr_bit;
	ct->chip.irq_unmask = irq_gc_mask_set_bit;
	ct->chip.irq_set_type = gpio_set_irq_type;
	ct->chip.irq_set_wake = gpio_set_wake_irq;
	ct->chip.flags = IRQCHIP_MASK_ON_SUSPEND;
	ct->regs.ack = GPIO_ISR;
	ct->regs.mask = GPIO_IMR;

	rv = devm_irq_setup_generic_chip(port->dev, gc, IRQ_MSK(32),
					 IRQ_GC_INIT_NESTED_LOCK,
					 IRQ_NOREQUEST, 0);

	return rv;
}