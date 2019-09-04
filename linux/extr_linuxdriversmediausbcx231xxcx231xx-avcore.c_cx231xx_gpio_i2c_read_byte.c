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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int tuner_scl_gpio; int tuner_sda_gpio; } ;
struct cx231xx {int gpio_val; int /*<<< orphan*/  gpio_dir; TYPE_1__ board; } ;

/* Variables and functions */
 int cx231xx_get_gpio_bit (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int cx231xx_set_gpio_bit (struct cx231xx*,int /*<<< orphan*/ ,int) ; 

int cx231xx_gpio_i2c_read_byte(struct cx231xx *dev, u8 *buf)
{
	u8 value = 0;
	int status = 0;
	u32 gpio_logic_value = 0;
	u8 i;

	/* read byte */
	for (i = 0; i < 8; i++) {	/* send write I2c addr */

		/* set SCL to output 0; set SDA to input */
		dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
		status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
					      dev->gpio_val);

		/* set SCL to output 1; set SDA to input */
		dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
		status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
					      dev->gpio_val);

		/* get SDA data bit */
		gpio_logic_value = dev->gpio_val;
		status = cx231xx_get_gpio_bit(dev, dev->gpio_dir,
					      &dev->gpio_val);
		if ((dev->gpio_val & (1 << dev->board.tuner_sda_gpio)) != 0)
			value |= (1 << (8 - i - 1));

		dev->gpio_val = gpio_logic_value;
	}

	/* set SCL to output 0,finish the read latest SCL signal.
	   !!!set SDA to input, never to modify SDA direction at
	   the same times */
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	/* store the value */
	*buf = value & 0xff;

	return status;
}