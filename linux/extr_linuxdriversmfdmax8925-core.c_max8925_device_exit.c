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
struct max8925_chip {int /*<<< orphan*/  dev; scalar_t__ tsc_irq; scalar_t__ core_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct max8925_chip*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 

void max8925_device_exit(struct max8925_chip *chip)
{
	if (chip->core_irq)
		free_irq(chip->core_irq, chip);
	if (chip->tsc_irq)
		free_irq(chip->tsc_irq, chip);
	mfd_remove_devices(chip->dev);
}