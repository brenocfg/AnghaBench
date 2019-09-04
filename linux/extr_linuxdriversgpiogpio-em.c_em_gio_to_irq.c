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
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_domain; } ;

/* Variables and functions */
 TYPE_1__* gpio_to_priv (struct gpio_chip*) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int em_gio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	return irq_create_mapping(gpio_to_priv(chip)->irq_domain, offset);
}