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
struct irq_chip {int dummy; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ MIPS_CPU_IRQ_CASCADE ; 
 int exin_avail ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 scalar_t__* ltq_eiu_irq ; 
 struct irq_chip ltq_eiu_type ; 
 struct irq_chip ltq_irq_type ; 

__attribute__((used)) static int icu_map(struct irq_domain *d, unsigned int irq, irq_hw_number_t hw)
{
	struct irq_chip *chip = &ltq_irq_type;
	int i;

	if (hw < MIPS_CPU_IRQ_CASCADE)
		return 0;

	for (i = 0; i < exin_avail; i++)
		if (hw == ltq_eiu_irq[i])
			chip = &ltq_eiu_type;

	irq_set_chip_and_handler(irq, chip, handle_level_irq);

	return 0;
}