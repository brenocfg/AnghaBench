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
typedef  int /*<<< orphan*/  u8 ;
struct tsl2563_chip {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int TSL2563_CMD ; 
 int /*<<< orphan*/  TSL2563_CMD_POWER_OFF ; 
 int /*<<< orphan*/  TSL2563_CMD_POWER_ON ; 
 int TSL2563_REG_CTRL ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsl2563_set_power(struct tsl2563_chip *chip, int on)
{
	struct i2c_client *client = chip->client;
	u8 cmd;

	cmd = on ? TSL2563_CMD_POWER_ON : TSL2563_CMD_POWER_OFF;
	return i2c_smbus_write_byte_data(client,
					 TSL2563_CMD | TSL2563_REG_CTRL, cmd);
}