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
struct cs5535_gpio_chip {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  errata_outl (struct cs5535_gpio_chip*,int,unsigned int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void __cs5535_gpio_set(struct cs5535_gpio_chip *chip, unsigned offset,
		unsigned int reg)
{
	if (offset < 16)
		/* low bank register */
		outl(1 << offset, chip->base + reg);
	else
		/* high bank register */
		errata_outl(chip, 1 << (offset - 16), reg);
}