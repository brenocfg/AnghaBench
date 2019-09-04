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
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int EINVAL ; 
 int GIU_IRQ_BASE ; 

__attribute__((used)) static int vr41xx_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	if (offset >= chip->ngpio)
		return -EINVAL;

	return GIU_IRQ_BASE + offset;
}