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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_hid_platform_data {int /*<<< orphan*/  post_power_delay_ms; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_property_read_u32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i2c_hid_fwnode_probe(struct i2c_client *client,
				 struct i2c_hid_platform_data *pdata)
{
	u32 val;

	if (!device_property_read_u32(&client->dev, "post-power-on-delay-ms",
				      &val))
		pdata->post_power_delay_ms = val;
}