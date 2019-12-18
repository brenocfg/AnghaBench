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
typedef  void* u32 ;
struct cx231xx {int gpio_dir; int gpio_val; } ;

/* Variables and functions */
 int EINVAL ; 
 int cx231xx_set_gpio_bit (struct cx231xx*,int,int) ; 

int cx231xx_set_gpio_value(struct cx231xx *dev, int pin_number, int pin_value)
{
	int status = 0;
	u32 value = 0;

	/* Check for valid pin_number - if 0xFF , bail out */
	if (pin_number >= 32)
		return -EINVAL;

	/* first do a sanity check - if the Pin is not output, make it output */
	if ((dev->gpio_dir & (1 << pin_number)) == 0x00) {
		/* It was in input mode */
		value = dev->gpio_dir | (1 << pin_number);
		dev->gpio_dir = value;
		status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
					      dev->gpio_val);
		value = 0;
	}

	if (pin_value == 0)
		value = dev->gpio_val & (~(1 << pin_number));
	else
		value = dev->gpio_val | (1 << pin_number);

	/* store the value */
	dev->gpio_val = value;

	/* toggle bit0 of GP_IO */
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	return status;
}