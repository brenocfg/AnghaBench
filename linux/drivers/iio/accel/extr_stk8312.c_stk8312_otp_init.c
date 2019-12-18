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
struct stk8312_data {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STK8312_REG_AFECTRL ; 
 int /*<<< orphan*/  STK8312_REG_OTPADDR ; 
 int /*<<< orphan*/  STK8312_REG_OTPCTRL ; 
 int /*<<< orphan*/  STK8312_REG_OTPDATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int stk8312_otp_init(struct stk8312_data *data)
{
	int ret;
	int count = 10;
	struct i2c_client *client = data->client;

	ret = i2c_smbus_write_byte_data(client, STK8312_REG_OTPADDR, 0x70);
	if (ret < 0)
		goto exit_err;
	ret = i2c_smbus_write_byte_data(client, STK8312_REG_OTPCTRL, 0x02);
	if (ret < 0)
		goto exit_err;

	do {
		usleep_range(1000, 5000);
		ret = i2c_smbus_read_byte_data(client, STK8312_REG_OTPCTRL);
		if (ret < 0)
			goto exit_err;
		count--;
	} while (!(ret & BIT(7)) && count > 0);

	if (count == 0) {
		ret = -ETIMEDOUT;
		goto exit_err;
	}

	ret = i2c_smbus_read_byte_data(client, STK8312_REG_OTPDATA);
	if (ret == 0)
		ret = -EINVAL;
	if (ret < 0)
		goto exit_err;

	ret = i2c_smbus_write_byte_data(data->client, STK8312_REG_AFECTRL, ret);
	if (ret < 0)
		goto exit_err;
	msleep(150);

	return 0;

exit_err:
	dev_err(&client->dev, "failed to initialize sensor\n");
	return ret;
}