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
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct mv88e6xxx_chip {int device_irq; TYPE_1__ g2_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv88e6xxx_g2_watchdog_free (struct mv88e6xxx_chip*) ; 

void mv88e6xxx_g2_irq_free(struct mv88e6xxx_chip *chip)
{
	int irq, virq;

	mv88e6xxx_g2_watchdog_free(chip);

	free_irq(chip->device_irq, chip);
	irq_dispose_mapping(chip->device_irq);

	for (irq = 0; irq < 16; irq++) {
		virq = irq_find_mapping(chip->g2_irq.domain, irq);
		irq_dispose_mapping(virq);
	}

	irq_domain_remove(chip->g2_irq.domain);
}