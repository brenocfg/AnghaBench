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
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  em_gio_write (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  gpio_to_priv (struct gpio_chip*) ; 

__attribute__((used)) static void __em_gio_set(struct gpio_chip *chip, unsigned int reg,
			 unsigned shift, int value)
{
	/* upper 16 bits contains mask and lower 16 actual value */
	em_gio_write(gpio_to_priv(chip), reg,
		     (BIT(shift + 16)) | (value << shift));
}