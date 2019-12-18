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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int _pmbus_write_word_data (struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmbus_fan_command_registers ; 
 int /*<<< orphan*/ * pmbus_fan_config_registers ; 
 int pmbus_read_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int pmbus_write_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ,int) ; 

int pmbus_update_fan(struct i2c_client *client, int page, int id,
		     u8 config, u8 mask, u16 command)
{
	int from;
	int rv;
	u8 to;

	from = pmbus_read_byte_data(client, page,
				    pmbus_fan_config_registers[id]);
	if (from < 0)
		return from;

	to = (from & ~mask) | (config & mask);
	if (to != from) {
		rv = pmbus_write_byte_data(client, page,
					   pmbus_fan_config_registers[id], to);
		if (rv < 0)
			return rv;
	}

	return _pmbus_write_word_data(client, page,
				      pmbus_fan_command_registers[id], command);
}