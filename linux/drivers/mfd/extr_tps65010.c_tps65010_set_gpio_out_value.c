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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENODEV ; 
 unsigned int GPIO1 ; 
 unsigned int GPIO4 ; 
#define  LOW 128 
 int /*<<< orphan*/  TPS_DEFGPIO ; 
 unsigned int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int,char*,unsigned int) ; 
 TYPE_1__* the_tps ; 

int tps65010_set_gpio_out_value(unsigned gpio, unsigned value)
{
	int	 status;
	unsigned defgpio;

	if (!the_tps)
		return -ENODEV;
	if ((gpio < GPIO1) || (gpio > GPIO4))
		return -EINVAL;

	mutex_lock(&the_tps->lock);

	defgpio = i2c_smbus_read_byte_data(the_tps->client, TPS_DEFGPIO);

	/* Configure GPIO for output */
	defgpio |= 1 << (gpio + 3);

	/* Writing 1 forces a logic 0 on that GPIO and vice versa */
	switch (value) {
	case LOW:
		defgpio |= 1 << (gpio - 1);    /* set GPIO low by writing 1 */
		break;
	/* case HIGH: */
	default:
		defgpio &= ~(1 << (gpio - 1)); /* set GPIO high by writing 0 */
		break;
	}

	status = i2c_smbus_write_byte_data(the_tps->client,
		TPS_DEFGPIO, defgpio);

	pr_debug("%s: gpio%dout = %s, defgpio 0x%02x\n", DRIVER_NAME,
		gpio, value ? "high" : "low",
		i2c_smbus_read_byte_data(the_tps->client, TPS_DEFGPIO));

	mutex_unlock(&the_tps->lock);
	return status;
}