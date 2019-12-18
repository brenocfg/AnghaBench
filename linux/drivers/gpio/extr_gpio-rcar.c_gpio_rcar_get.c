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
typedef  int u32 ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  INDT ; 
 int /*<<< orphan*/  INOUTSEL ; 
 int /*<<< orphan*/  OUTDT ; 
 int gpio_rcar_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int gpio_rcar_get(struct gpio_chip *chip, unsigned offset)
{
	u32 bit = BIT(offset);

	/* testing on r8a7790 shows that INDT does not show correct pin state
	 * when configured as output, so use OUTDT in case of output pins */
	if (gpio_rcar_read(gpiochip_get_data(chip), INOUTSEL) & bit)
		return !!(gpio_rcar_read(gpiochip_get_data(chip), OUTDT) & bit);
	else
		return !!(gpio_rcar_read(gpiochip_get_data(chip), INDT) & bit);
}