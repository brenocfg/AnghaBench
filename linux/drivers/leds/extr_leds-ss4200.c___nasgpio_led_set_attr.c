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
 int /*<<< orphan*/  outl (int,int) ; 

__attribute__((used)) static void __nasgpio_led_set_attr(struct led_classdev *led_cdev,
				   u32 port, u32 value)
{
	struct nasgpio_led *led = led_classdev_to_nasgpio_led(led_cdev);
	u32 gpio_out;

	gpio_out = inl(nas_gpio_io_base + port);
	if (value)
		gpio_out |= (1<<led->gpio_bit);
	else
		gpio_out &= ~(1<<led->gpio_bit);

	outl(gpio_out, nas_gpio_io_base + port);
}