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
typedef  scalar_t__ u8 ;
struct ziirave_wdt_rev {int major; int minor; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (struct i2c_client*,scalar_t__) ; 

__attribute__((used)) static int ziirave_wdt_revision(struct i2c_client *client,
				struct ziirave_wdt_rev *rev, u8 command)
{
	int ret;

	ret = i2c_smbus_read_byte_data(client, command);
	if (ret < 0)
		return ret;

	rev->major = ret;

	ret = i2c_smbus_read_byte_data(client, command + 1);
	if (ret < 0)
		return ret;

	rev->minor = ret;

	return 0;
}