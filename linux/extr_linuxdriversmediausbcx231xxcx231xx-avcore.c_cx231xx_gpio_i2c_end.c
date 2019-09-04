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
struct TYPE_2__ {int tuner_scl_gpio; int tuner_sda_gpio; } ;
struct cx231xx {int gpio_dir; int gpio_val; TYPE_1__ board; } ;

/* Variables and functions */
 int EINVAL ; 
 int cx231xx_set_gpio_bit (struct cx231xx*,int,int) ; 

int cx231xx_gpio_i2c_end(struct cx231xx *dev)
{
	int status = 0;

	/* set SCL to output 0; set SDA to output 0      */
	dev->gpio_dir |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_dir |= 1 << dev->board.tuner_sda_gpio;

	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	if (status < 0)
		return -EINVAL;

	/* set SCL to output 1; set SDA to output 0      */
	dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	if (status < 0)
		return -EINVAL;

	/* set SCL to input ,release SCL cable control
	   set SDA to input ,release SDA cable control */
	dev->gpio_dir &= ~(1 << dev->board.tuner_scl_gpio);
	dev->gpio_dir &= ~(1 << dev->board.tuner_sda_gpio);

	status =
	    cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	if (status < 0)
		return -EINVAL;

	return status;
}