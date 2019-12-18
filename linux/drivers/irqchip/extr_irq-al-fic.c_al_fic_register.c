#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct irq_chip_generic {struct al_fic* private; TYPE_3__* chip_types; int /*<<< orphan*/  reg_base; } ;
struct device_node {int dummy; } ;
struct al_fic {int /*<<< orphan*/  domain; int /*<<< orphan*/  parent_irq; int /*<<< orphan*/  base; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  irq_retrigger; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  ack; int /*<<< orphan*/  mask; } ;
struct TYPE_6__ {TYPE_2__ chip; TYPE_1__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FIC_CAUSE ; 
 int /*<<< orphan*/  AL_FIC_MASK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQCHIP_SKIP_SET_WAKE ; 
 int /*<<< orphan*/  IRQ_GC_INIT_MASK_CACHE ; 
 int /*<<< orphan*/  NR_FIC_IRQS ; 
 int /*<<< orphan*/  al_fic_irq_handler ; 
 int /*<<< orphan*/  al_fic_irq_retrigger ; 
 int /*<<< orphan*/  al_fic_irq_set_type ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_alloc_domain_generic_chips (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct al_fic*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_gc_ack_clr_bit ; 
 int /*<<< orphan*/  irq_gc_mask_clr_bit ; 
 int /*<<< orphan*/  irq_gc_mask_set_bit ; 
 int /*<<< orphan*/  irq_generic_chip_ops ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct al_fic*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int al_fic_register(struct device_node *node,
			   struct al_fic *fic)
{
	struct irq_chip_generic *gc;
	int ret;

	fic->domain = irq_domain_add_linear(node,
					    NR_FIC_IRQS,
					    &irq_generic_chip_ops,
					    fic);
	if (!fic->domain) {
		pr_err("fail to add irq domain\n");
		return -ENOMEM;
	}

	ret = irq_alloc_domain_generic_chips(fic->domain,
					     NR_FIC_IRQS,
					     1, fic->name,
					     handle_level_irq,
					     0, 0, IRQ_GC_INIT_MASK_CACHE);
	if (ret) {
		pr_err("fail to allocate generic chip (%d)\n", ret);
		goto err_domain_remove;
	}

	gc = irq_get_domain_generic_chip(fic->domain, 0);
	gc->reg_base = fic->base;
	gc->chip_types->regs.mask = AL_FIC_MASK;
	gc->chip_types->regs.ack = AL_FIC_CAUSE;
	gc->chip_types->chip.irq_mask = irq_gc_mask_set_bit;
	gc->chip_types->chip.irq_unmask = irq_gc_mask_clr_bit;
	gc->chip_types->chip.irq_ack = irq_gc_ack_clr_bit;
	gc->chip_types->chip.irq_set_type = al_fic_irq_set_type;
	gc->chip_types->chip.irq_retrigger = al_fic_irq_retrigger;
	gc->chip_types->chip.flags = IRQCHIP_SKIP_SET_WAKE;
	gc->private = fic;

	irq_set_chained_handler_and_data(fic->parent_irq,
					 al_fic_irq_handler,
					 fic);
	return 0;

err_domain_remove:
	irq_domain_remove(fic->domain);

	return ret;
}