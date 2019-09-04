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
struct irq_domain {int dummy; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  i8259_pic ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int) ; 

__attribute__((used)) static int i8259_host_map(struct irq_domain *h, unsigned int virq,
			  irq_hw_number_t hw)
{
	pr_debug("i8259_host_map(%d, 0x%lx)\n", virq, hw);

	/* We block the internal cascade */
	if (hw == 2)
		irq_set_status_flags(virq, IRQ_NOREQUEST);

	/* We use the level handler only for now, we might want to
	 * be more cautious here but that works for now
	 */
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &i8259_pic, handle_level_irq);
	return 0;
}