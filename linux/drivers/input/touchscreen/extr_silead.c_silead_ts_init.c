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
struct silead_ts_data {int /*<<< orphan*/  max_fingers; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SILEAD_CLOCK ; 
 int /*<<< orphan*/  SILEAD_CMD_RESET ; 
 int /*<<< orphan*/  SILEAD_CMD_SLEEP_MAX ; 
 int /*<<< orphan*/  SILEAD_CMD_SLEEP_MIN ; 
 int /*<<< orphan*/  SILEAD_CMD_START ; 
 int /*<<< orphan*/  SILEAD_REG_CLOCK ; 
 int /*<<< orphan*/  SILEAD_REG_RESET ; 
 int /*<<< orphan*/  SILEAD_REG_TOUCH_NR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct silead_ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int silead_ts_init(struct i2c_client *client)
{
	struct silead_ts_data *data = i2c_get_clientdata(client);
	int error;

	error = i2c_smbus_write_byte_data(client, SILEAD_REG_RESET,
					  SILEAD_CMD_RESET);
	if (error)
		goto i2c_write_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	error = i2c_smbus_write_byte_data(client, SILEAD_REG_TOUCH_NR,
					data->max_fingers);
	if (error)
		goto i2c_write_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	error = i2c_smbus_write_byte_data(client, SILEAD_REG_CLOCK,
					  SILEAD_CLOCK);
	if (error)
		goto i2c_write_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	error = i2c_smbus_write_byte_data(client, SILEAD_REG_RESET,
					  SILEAD_CMD_START);
	if (error)
		goto i2c_write_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	return 0;

i2c_write_err:
	dev_err(&client->dev, "Registers clear error %d\n", error);
	return error;
}