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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ZIIRAVE_WDT_RESET_DURATION ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,...) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int reset_duration ; 

__attribute__((used)) static int ziirave_wdt_init_duration(struct i2c_client *client)
{
	int ret;

	if (!reset_duration) {
		/* See if the reset pulse duration is provided in an of_node */
		if (!client->dev.of_node)
			ret = -ENODEV;
		else
			ret = of_property_read_u32(client->dev.of_node,
						   "reset-duration-ms",
						   &reset_duration);
		if (ret) {
			dev_info(&client->dev,
			 "No reset pulse duration specified, using default\n");
			return 0;
		}
	}

	if (reset_duration < 1 || reset_duration > 255)
		return -EINVAL;

	dev_info(&client->dev, "Setting reset duration to %dms",
		 reset_duration);

	return i2c_smbus_write_byte_data(client, ZIIRAVE_WDT_RESET_DURATION,
					 reset_duration);
}