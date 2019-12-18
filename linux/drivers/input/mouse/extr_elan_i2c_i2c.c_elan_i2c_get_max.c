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
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_I2C_MAX_X_AXIS_CMD ; 
 int /*<<< orphan*/  ETP_I2C_MAX_Y_AXIS_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int elan_i2c_read_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elan_i2c_get_max(struct i2c_client *client,
			    unsigned int *max_x, unsigned int *max_y)
{
	int error;
	u8 val[3];

	error = elan_i2c_read_cmd(client, ETP_I2C_MAX_X_AXIS_CMD, val);
	if (error) {
		dev_err(&client->dev, "failed to get X dimension: %d\n", error);
		return error;
	}

	*max_x = le16_to_cpup((__le16 *)val) & 0x0fff;

	error = elan_i2c_read_cmd(client, ETP_I2C_MAX_Y_AXIS_CMD, val);
	if (error) {
		dev_err(&client->dev, "failed to get Y dimension: %d\n", error);
		return error;
	}

	*max_y = le16_to_cpup((__le16 *)val) & 0x0fff;

	return 0;
}