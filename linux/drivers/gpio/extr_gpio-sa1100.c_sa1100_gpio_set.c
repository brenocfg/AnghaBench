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
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int R_GPCR ; 
 int R_GPSR ; 
 TYPE_1__* sa1100_gpio_chip (struct gpio_chip*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sa1100_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	int reg = value ? R_GPSR : R_GPCR;

	writel_relaxed(BIT(offset), sa1100_gpio_chip(chip)->membase + reg);
}