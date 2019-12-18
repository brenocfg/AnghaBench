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
struct wm8350_gpio_data {struct wm8350* wm8350; } ;
struct wm8350 {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_GPIO_LEVEL ; 
 struct wm8350_gpio_data* gpiochip_get_data (struct gpio_chip*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct wm8350_gpio_data *wm8350_gpio = gpiochip_get_data(chip);
	struct wm8350 *wm8350 = wm8350_gpio->wm8350;
	int ret;

	ret = wm8350_reg_read(wm8350, WM8350_GPIO_LEVEL);
	if (ret < 0)
		return ret;

	if (ret & (1 << offset))
		return 1;
	else
		return 0;
}