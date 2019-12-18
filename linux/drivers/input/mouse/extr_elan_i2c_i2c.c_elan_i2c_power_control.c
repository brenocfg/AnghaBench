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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_DISABLE_POWER ; 
 int /*<<< orphan*/  ETP_I2C_POWER_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int elan_i2c_read_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int elan_i2c_write_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elan_i2c_power_control(struct i2c_client *client, bool enable)
{
	u8 val[2];
	u16 reg;
	int error;

	error = elan_i2c_read_cmd(client, ETP_I2C_POWER_CMD, val);
	if (error) {
		dev_err(&client->dev,
			"failed to read current power state: %d\n",
			error);
		return error;
	}

	reg = le16_to_cpup((__le16 *)val);
	if (enable)
		reg &= ~ETP_DISABLE_POWER;
	else
		reg |= ETP_DISABLE_POWER;

	error = elan_i2c_write_cmd(client, ETP_I2C_POWER_CMD, reg);
	if (error) {
		dev_err(&client->dev,
			"failed to write current power state: %d\n",
			error);
		return error;
	}

	return 0;
}