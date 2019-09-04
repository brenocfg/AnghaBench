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
 int /*<<< orphan*/  GIO_OH ; 
 int /*<<< orphan*/  GIO_OL ; 
 int /*<<< orphan*/  __em_gio_set (struct gpio_chip*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void em_gio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	/* output is split into two registers */
	if (offset < 16)
		__em_gio_set(chip, GIO_OL, offset, value);
	else
		__em_gio_set(chip, GIO_OH, offset - 16, value);
}