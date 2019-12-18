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
struct irq_info {int refcnt; int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQT_UNBOUND ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_get_affinity_mask (unsigned int) ; 
 int /*<<< orphan*/  irq_set_handler_data (unsigned int,struct irq_info*) ; 
 struct irq_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 
 int /*<<< orphan*/  xen_irq_list_head ; 

__attribute__((used)) static void xen_irq_init(unsigned irq)
{
	struct irq_info *info;
#ifdef CONFIG_SMP
	/* By default all event channels notify CPU#0. */
	cpumask_copy(irq_get_affinity_mask(irq), cpumask_of(0));
#endif

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL)
		panic("Unable to allocate metadata for IRQ%d\n", irq);

	info->type = IRQT_UNBOUND;
	info->refcnt = -1;

	irq_set_handler_data(irq, info);

	list_add_tail(&info->list, &xen_irq_list_head);
}