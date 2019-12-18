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
struct TYPE_6__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  masked; int /*<<< orphan*/  chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  domain; } ;
struct mv88e6xxx_chip {int device_irq; TYPE_3__ g2_irq; TYPE_2__ g1_irq; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int MV88E6XXX_G1_STS_IRQ_DEVICE ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  irq_domain_add_simple (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 void* irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv88e6xxx_g2_irq_chip ; 
 int /*<<< orphan*/  mv88e6xxx_g2_irq_domain_ops ; 
 int /*<<< orphan*/  mv88e6xxx_g2_irq_thread_fn ; 
 int mv88e6xxx_g2_watchdog_setup (struct mv88e6xxx_chip*) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mv88e6xxx_chip*) ; 

int mv88e6xxx_g2_irq_setup(struct mv88e6xxx_chip *chip)
{
	int err, irq, virq;

	chip->g2_irq.domain = irq_domain_add_simple(
		chip->dev->of_node, 16, 0, &mv88e6xxx_g2_irq_domain_ops, chip);
	if (!chip->g2_irq.domain)
		return -ENOMEM;

	for (irq = 0; irq < 16; irq++)
		irq_create_mapping(chip->g2_irq.domain, irq);

	chip->g2_irq.chip = mv88e6xxx_g2_irq_chip;
	chip->g2_irq.masked = ~0;

	chip->device_irq = irq_find_mapping(chip->g1_irq.domain,
					    MV88E6XXX_G1_STS_IRQ_DEVICE);
	if (chip->device_irq < 0) {
		err = chip->device_irq;
		goto out;
	}

	err = request_threaded_irq(chip->device_irq, NULL,
				   mv88e6xxx_g2_irq_thread_fn,
				   IRQF_ONESHOT, "mv88e6xxx-g2", chip);
	if (err)
		goto out;

	return mv88e6xxx_g2_watchdog_setup(chip);

out:
	for (irq = 0; irq < 16; irq++) {
		virq = irq_find_mapping(chip->g2_irq.domain, irq);
		irq_dispose_mapping(virq);
	}

	irq_domain_remove(chip->g2_irq.domain);

	return err;
}