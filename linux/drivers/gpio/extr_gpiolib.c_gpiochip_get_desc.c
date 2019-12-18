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
typedef  size_t u16 ;
struct gpio_device {size_t ngpio; struct gpio_desc* descs; } ;
struct gpio_desc {int dummy; } ;
struct gpio_chip {struct gpio_device* gpiodev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 

struct gpio_desc *gpiochip_get_desc(struct gpio_chip *chip,
				    u16 hwnum)
{
	struct gpio_device *gdev = chip->gpiodev;

	if (hwnum >= gdev->ngpio)
		return ERR_PTR(-EINVAL);

	return &gdev->descs[hwnum];
}