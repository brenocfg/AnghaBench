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
typedef  int /*<<< orphan*/  u8 ;
struct max8997_led {int enabled; TYPE_1__* iodev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct i2c_client* i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8997_LED_BOOST_ENABLE_MASK ; 
 int /*<<< orphan*/  MAX8997_REG_BOOST_CNTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max8997_update_reg (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max8997_led_enable(struct max8997_led *led, bool enable)
{
	int ret;
	struct i2c_client *client = led->iodev->i2c;
	u8 val = 0, mask = MAX8997_LED_BOOST_ENABLE_MASK;

	if (led->enabled == enable)
		return;

	val = enable ? MAX8997_LED_BOOST_ENABLE_MASK : 0;

	ret = max8997_update_reg(client, MAX8997_REG_BOOST_CNTL, val, mask);
	if (ret)
		dev_err(led->iodev->dev,
			"failed to update register(%d)\n", ret);

	led->enabled = enable;
}