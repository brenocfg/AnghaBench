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
struct wm8994_gpio {struct wm8994* wm8994; } ;
struct wm8994 {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int WM8994_GPIO_1 ; 
 int WM8994_GPN_LVL ; 
 struct wm8994_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  wm8994_set_bits (struct wm8994*,unsigned int,int,int) ; 

__attribute__((used)) static void wm8994_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	struct wm8994 *wm8994 = wm8994_gpio->wm8994;

	if (value)
		value = WM8994_GPN_LVL;

	wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset, WM8994_GPN_LVL, value);
}