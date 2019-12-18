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
struct pm860x_chip {scalar_t__ core_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct pm860x_chip*) ; 

__attribute__((used)) static void device_irq_exit(struct pm860x_chip *chip)
{
	if (chip->core_irq)
		free_irq(chip->core_irq, chip);
}