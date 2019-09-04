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
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ gpio_is_valid (unsigned int) ; 
 struct gpio_desc* gpio_to_desc (unsigned int) ; 
 int gpiod_request (struct gpio_desc*,char const*) ; 

int gpio_request(unsigned gpio, const char *label)
{
	struct gpio_desc *desc = gpio_to_desc(gpio);

	/* Compatibility: assume unavailable "valid" GPIOs will appear later */
	if (!desc && gpio_is_valid(gpio))
		return -EPROBE_DEFER;

	return gpiod_request(desc, label);
}