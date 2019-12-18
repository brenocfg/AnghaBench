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
struct TYPE_2__ {scalar_t__ membase; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ R_GPLR ; 
 int readl_relaxed (scalar_t__) ; 
 TYPE_1__* sa1100_gpio_chip (struct gpio_chip*) ; 

__attribute__((used)) static int sa1100_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	return readl_relaxed(sa1100_gpio_chip(chip)->membase + R_GPLR) &
		BIT(offset);
}