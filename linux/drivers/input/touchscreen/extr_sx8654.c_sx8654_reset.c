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
struct sx8654 {TYPE_1__* client; scalar_t__ gpio_reset; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_REG_SOFTRESET ; 
 int /*<<< orphan*/  SOFTRESET_VALUE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sx8654_reset(struct sx8654 *ts)
{
	int err;

	if (ts->gpio_reset) {
		gpiod_set_value_cansleep(ts->gpio_reset, 1);
		udelay(2); /* Tpulse > 1µs */
		gpiod_set_value_cansleep(ts->gpio_reset, 0);
	} else {
		dev_dbg(&ts->client->dev, "NRST unavailable, try softreset\n");
		err = i2c_smbus_write_byte_data(ts->client, I2C_REG_SOFTRESET,
						SOFTRESET_VALUE);
		if (err)
			return err;
	}

	return 0;
}