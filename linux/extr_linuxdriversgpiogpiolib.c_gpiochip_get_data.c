#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {TYPE_1__* gpiodev; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */

void *gpiochip_get_data(struct gpio_chip *chip)
{
	return chip->gpiodev->data;
}