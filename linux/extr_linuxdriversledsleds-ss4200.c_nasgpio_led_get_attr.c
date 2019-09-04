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
struct nasgpio_led {int gpio_bit; } ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int inl (int) ; 
 struct nasgpio_led* led_classdev_to_nasgpio_led (struct led_classdev*) ; 
 int nas_gpio_io_base ; 
 int /*<<< orphan*/  nasgpio_gpio_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 nasgpio_led_get_attr(struct led_classdev *led_cdev, u32 port)
{
	struct nasgpio_led *led = led_classdev_to_nasgpio_led(led_cdev);
	u32 gpio_in;

	spin_lock(&nasgpio_gpio_lock);
	gpio_in = inl(nas_gpio_io_base + port);
	spin_unlock(&nasgpio_gpio_lock);
	if (gpio_in & (1<<led->gpio_bit))
		return 1;
	return 0;
}