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
struct irq_domain {int dummy; } ;
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ICOLL ; 
 struct irq_chip asm9260_icoll_chip ; 
 int /*<<< orphan*/  handle_level_irq ; 
 TYPE_1__ icoll_priv ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 struct irq_chip mxs_icoll_chip ; 

__attribute__((used)) static int icoll_irq_domain_map(struct irq_domain *d, unsigned int virq,
				irq_hw_number_t hw)
{
	struct irq_chip *chip;

	if (icoll_priv.type == ICOLL)
		chip = &mxs_icoll_chip;
	else
		chip = &asm9260_icoll_chip;

	irq_set_chip_and_handler(virq, chip, handle_level_irq);

	return 0;
}