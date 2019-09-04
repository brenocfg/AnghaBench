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
typedef  int uint8_t ;
struct rc5t583_gpio {TYPE_1__* rc5t583; } ;
struct gpio_chip {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  RC5T583_GPIO_MON_IOIN ; 
 struct rc5t583_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int rc5t583_read (struct device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int rc5t583_gpio_get(struct gpio_chip *gc, unsigned int offset)
{
	struct rc5t583_gpio *rc5t583_gpio = gpiochip_get_data(gc);
	struct device *parent = rc5t583_gpio->rc5t583->dev;
	uint8_t val = 0;
	int ret;

	ret = rc5t583_read(parent, RC5T583_GPIO_MON_IOIN, &val);
	if (ret < 0)
		return ret;

	return !!(val & BIT(offset));
}