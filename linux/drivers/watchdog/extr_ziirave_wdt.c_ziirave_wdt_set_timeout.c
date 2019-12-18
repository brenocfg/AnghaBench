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
struct watchdog_device {unsigned int timeout; int /*<<< orphan*/  parent; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIIRAVE_WDT_TIMEOUT ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ziirave_wdt_set_timeout(struct watchdog_device *wdd,
				   unsigned int timeout)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	int ret;

	ret = i2c_smbus_write_byte_data(client, ZIIRAVE_WDT_TIMEOUT, timeout);
	if (!ret)
		wdd->timeout = timeout;

	return ret;
}