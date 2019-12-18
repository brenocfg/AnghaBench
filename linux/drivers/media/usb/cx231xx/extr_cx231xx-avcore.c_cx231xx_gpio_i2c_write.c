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
typedef  int u8 ;
struct cx231xx {int /*<<< orphan*/  gpio_i2c_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx231xx_gpio_i2c_end (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_gpio_i2c_read_ack (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_gpio_i2c_start (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_gpio_i2c_write_byte (struct cx231xx*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cx231xx_gpio_i2c_write(struct cx231xx *dev, u8 dev_addr, u8 *buf, u8 len)
{
	int i = 0;

	/* get the lock */
	mutex_lock(&dev->gpio_i2c_lock);

	/* start */
	cx231xx_gpio_i2c_start(dev);

	/* write dev_addr */
	cx231xx_gpio_i2c_write_byte(dev, dev_addr << 1);

	/* read Ack */
	cx231xx_gpio_i2c_read_ack(dev);

	for (i = 0; i < len; i++) {
		/* Write data */
		cx231xx_gpio_i2c_write_byte(dev, buf[i]);

		/* read Ack */
		cx231xx_gpio_i2c_read_ack(dev);
	}

	/* write End */
	cx231xx_gpio_i2c_end(dev);

	/* release the lock */
	mutex_unlock(&dev->gpio_i2c_lock);

	return 0;
}