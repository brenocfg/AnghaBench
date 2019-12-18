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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct bu21013_ts {struct i2c_client* client; } ;

/* Variables and functions */
 int BU21013_CLK_MODE_CALIB ; 
 int BU21013_CLK_MODE_DIV ; 
 int /*<<< orphan*/  BU21013_CLK_MODE_REG ; 
 int BU21013_DELTA_0_6 ; 
 int BU21013_DONE ; 
 int /*<<< orphan*/  BU21013_DONE_REG ; 
 int BU21013_FILTER_EN ; 
 int /*<<< orphan*/  BU21013_FILTER_REG ; 
 int BU21013_GAIN_0 ; 
 int BU21013_GAIN_1 ; 
 int /*<<< orphan*/  BU21013_GAIN_REG ; 
 int BU21013_IDLET_0 ; 
 int BU21013_IDLE_INTERMIT_EN ; 
 int /*<<< orphan*/  BU21013_IDLE_REG ; 
 int BU21013_INT_MODE_LEVEL ; 
 int /*<<< orphan*/  BU21013_INT_MODE_REG ; 
 int BU21013_OFFSET_MODE_DEFAULT ; 
 int /*<<< orphan*/  BU21013_OFFSET_MODE_REG ; 
 int BU21013_POS_MODE1_0 ; 
 int BU21013_POS_MODE1_1 ; 
 int /*<<< orphan*/  BU21013_POS_MODE1_REG ; 
 int BU21013_POS_MODE2_AVG1 ; 
 int BU21013_POS_MODE2_AVG2 ; 
 int BU21013_POS_MODE2_EN_RAW ; 
 int BU21013_POS_MODE2_MULTI ; 
 int /*<<< orphan*/  BU21013_POS_MODE2_REG ; 
 int BU21013_POS_MODE2_ZERO ; 
 int BU21013_RESET_ENABLE ; 
 int /*<<< orphan*/  BU21013_RESET_REG ; 
 int BU21013_SENSORS_EN_0_7 ; 
 int BU21013_SENSORS_EN_16_23 ; 
 int BU21013_SENSORS_EN_8_15 ; 
 int /*<<< orphan*/  BU21013_SENSOR_0_7_REG ; 
 int /*<<< orphan*/  BU21013_SENSOR_16_23_REG ; 
 int /*<<< orphan*/  BU21013_SENSOR_8_15_REG ; 
 int BU21013_TH_OFF_3 ; 
 int BU21013_TH_OFF_4 ; 
 int /*<<< orphan*/  BU21013_TH_OFF_REG ; 
 int BU21013_TH_ON_5 ; 
 int /*<<< orphan*/  BU21013_TH_ON_REG ; 
 int /*<<< orphan*/  BU21013_XY_EDGE_REG ; 
 int BU21013_X_EDGE_0 ; 
 int BU21013_X_EDGE_2 ; 
 int BU21013_Y_EDGE_1 ; 
 int BU21013_Y_EDGE_3 ; 
 int /*<<< orphan*/  RESET_DELAY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bu21013_init_chip(struct bu21013_ts *ts)
{
	struct i2c_client *client = ts->client;
	int error;

	error = i2c_smbus_write_byte_data(client, BU21013_RESET_REG,
					  BU21013_RESET_ENABLE);
	if (error) {
		dev_err(&client->dev, "BU21013_RESET reg write failed\n");
		return error;
	}
	msleep(RESET_DELAY);

	error = i2c_smbus_write_byte_data(client, BU21013_SENSOR_0_7_REG,
					  BU21013_SENSORS_EN_0_7);
	if (error) {
		dev_err(&client->dev, "BU21013_SENSOR_0_7 reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_SENSOR_8_15_REG,
					  BU21013_SENSORS_EN_8_15);
	if (error) {
		dev_err(&client->dev, "BU21013_SENSOR_8_15 reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_SENSOR_16_23_REG,
					  BU21013_SENSORS_EN_16_23);
	if (error) {
		dev_err(&client->dev, "BU21013_SENSOR_16_23 reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_POS_MODE1_REG,
					  BU21013_POS_MODE1_0 |
						BU21013_POS_MODE1_1);
	if (error) {
		dev_err(&client->dev, "BU21013_POS_MODE1 reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_POS_MODE2_REG,
					  BU21013_POS_MODE2_ZERO |
						BU21013_POS_MODE2_AVG1 |
						BU21013_POS_MODE2_AVG2 |
						BU21013_POS_MODE2_EN_RAW |
						BU21013_POS_MODE2_MULTI);
	if (error) {
		dev_err(&client->dev, "BU21013_POS_MODE2 reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_CLK_MODE_REG,
					  BU21013_CLK_MODE_DIV |
						BU21013_CLK_MODE_CALIB);
	if (error) {
		dev_err(&client->dev, "BU21013_CLK_MODE reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_IDLE_REG,
					  BU21013_IDLET_0 |
						BU21013_IDLE_INTERMIT_EN);
	if (error) {
		dev_err(&client->dev, "BU21013_IDLE reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_INT_MODE_REG,
					  BU21013_INT_MODE_LEVEL);
	if (error) {
		dev_err(&client->dev, "BU21013_INT_MODE reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_FILTER_REG,
					  BU21013_DELTA_0_6 |
						BU21013_FILTER_EN);
	if (error) {
		dev_err(&client->dev, "BU21013_FILTER reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_TH_ON_REG,
					  BU21013_TH_ON_5);
	if (error) {
		dev_err(&client->dev, "BU21013_TH_ON reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_TH_OFF_REG,
					  BU21013_TH_OFF_4 | BU21013_TH_OFF_3);
	if (error) {
		dev_err(&client->dev, "BU21013_TH_OFF reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_GAIN_REG,
					  BU21013_GAIN_0 | BU21013_GAIN_1);
	if (error) {
		dev_err(&client->dev, "BU21013_GAIN reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_OFFSET_MODE_REG,
					  BU21013_OFFSET_MODE_DEFAULT);
	if (error) {
		dev_err(&client->dev, "BU21013_OFFSET_MODE reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_XY_EDGE_REG,
					  BU21013_X_EDGE_0 |
						BU21013_X_EDGE_2 |
						BU21013_Y_EDGE_1 |
						BU21013_Y_EDGE_3);
	if (error) {
		dev_err(&client->dev, "BU21013_XY_EDGE reg write failed\n");
		return error;
	}

	error = i2c_smbus_write_byte_data(client, BU21013_DONE_REG,
					  BU21013_DONE);
	if (error) {
		dev_err(&client->dev, "BU21013_REG_DONE reg write failed\n");
		return error;
	}

	return 0;
}