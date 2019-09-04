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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSL4531_CONTROL ; 
 int /*<<< orphan*/  TSL4531_MODE_POWERDOWN ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsl4531_powerdown(struct i2c_client *client)
{
	return i2c_smbus_write_byte_data(client, TSL4531_CONTROL,
		TSL4531_MODE_POWERDOWN);
}