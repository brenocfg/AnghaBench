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
struct winbond_gpio_info {int /*<<< orphan*/  invreg; int /*<<< orphan*/  datareg; int /*<<< orphan*/  dev; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned long* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  winbond_gpio_get_info (unsigned int*,struct winbond_gpio_info const**) ; 
 int winbond_sio_enter (unsigned long) ; 
 int /*<<< orphan*/  winbond_sio_leave (unsigned long) ; 
 int winbond_sio_reg_btest (unsigned long,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  winbond_sio_select_logical (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int winbond_gpio_get(struct gpio_chip *gc, unsigned int offset)
{
	unsigned long *base = gpiochip_get_data(gc);
	const struct winbond_gpio_info *info;
	bool val;

	winbond_gpio_get_info(&offset, &info);

	val = winbond_sio_enter(*base);
	if (val)
		return val;

	winbond_sio_select_logical(*base, info->dev);

	val = winbond_sio_reg_btest(*base, info->datareg, offset);
	if (winbond_sio_reg_btest(*base, info->invreg, offset))
		val = !val;

	winbond_sio_leave(*base);

	return val;
}