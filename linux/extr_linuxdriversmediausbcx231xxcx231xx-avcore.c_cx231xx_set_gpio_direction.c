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
struct cx231xx {int gpio_dir; int /*<<< orphan*/  gpio_val; } ;

/* Variables and functions */
 int EINVAL ; 
 int cx231xx_set_gpio_bit (struct cx231xx*,int,int /*<<< orphan*/ ) ; 

int cx231xx_set_gpio_direction(struct cx231xx *dev,
			       int pin_number, int pin_value)
{
	int status = 0;
	u32 value = 0;

	/* Check for valid pin_number - if 32 , bail out */
	if (pin_number >= 32)
		return -EINVAL;

	/* input */
	if (pin_value == 0)
		value = dev->gpio_dir & (~(1 << pin_number));	/* clear */
	else
		value = dev->gpio_dir | (1 << pin_number);

	status = cx231xx_set_gpio_bit(dev, value, dev->gpio_val);

	/* cache the value for future */
	dev->gpio_dir = value;

	return status;
}