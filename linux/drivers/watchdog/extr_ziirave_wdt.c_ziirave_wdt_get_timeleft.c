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
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIIRAVE_WDT_TIME_LEFT ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ziirave_wdt_get_timeleft(struct watchdog_device *wdd)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	int ret;

	ret = i2c_smbus_read_byte_data(client, ZIIRAVE_WDT_TIME_LEFT);
	if (ret < 0)
		ret = 0;

	return ret;
}