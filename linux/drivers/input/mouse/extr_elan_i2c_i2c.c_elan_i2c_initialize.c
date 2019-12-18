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
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_I2C_DESC_CMD ; 
 int /*<<< orphan*/  ETP_I2C_DESC_LENGTH ; 
 int /*<<< orphan*/  ETP_I2C_INF_LENGTH ; 
 int /*<<< orphan*/  ETP_I2C_REPORT_DESC_CMD ; 
 int /*<<< orphan*/  ETP_I2C_REPORT_DESC_LENGTH ; 
 int /*<<< orphan*/  ETP_I2C_RESET ; 
 int /*<<< orphan*/  ETP_I2C_STAND_CMD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int elan_i2c_read_block (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int elan_i2c_write_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int elan_i2c_initialize(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	int error;
	u8 val[256];

	error = elan_i2c_write_cmd(client, ETP_I2C_STAND_CMD, ETP_I2C_RESET);
	if (error) {
		dev_err(dev, "device reset failed: %d\n", error);
		return error;
	}

	/* Wait for the device to reset */
	msleep(100);

	/* get reset acknowledgement 0000 */
	error = i2c_master_recv(client, val, ETP_I2C_INF_LENGTH);
	if (error < 0) {
		dev_err(dev, "failed to read reset response: %d\n", error);
		return error;
	}

	error = elan_i2c_read_block(client, ETP_I2C_DESC_CMD,
				    val, ETP_I2C_DESC_LENGTH);
	if (error) {
		dev_err(dev, "cannot get device descriptor: %d\n", error);
		return error;
	}

	error = elan_i2c_read_block(client, ETP_I2C_REPORT_DESC_CMD,
				    val, ETP_I2C_REPORT_DESC_LENGTH);
	if (error) {
		dev_err(dev, "fetching report descriptor failed.: %d\n", error);
		return error;
	}

	return 0;
}