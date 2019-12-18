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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPE0A_PME_B0_VIRT_GPIO_PIN ; 
 int /*<<< orphan*/  bitmap_clear (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int0002_init_irq_valid_mask(struct gpio_chip *chip,
					unsigned long *valid_mask,
					unsigned int ngpios)
{
	bitmap_clear(valid_mask, 0, GPE0A_PME_B0_VIRT_GPIO_PIN);
}