#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mag3110_data {int ctrl_reg1; int sleep_val; TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int MAG3110_CTRL_AC ; 
 int /*<<< orphan*/  MAG3110_CTRL_REG1 ; 
 int MAG3110_CTRL_TM ; 
 int /*<<< orphan*/  MAG3110_STATUS ; 
 int MAG3110_STATUS_DRDY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mag3110_request(struct mag3110_data *data)
{
	int ret, tries = 150;

	if ((data->ctrl_reg1 & MAG3110_CTRL_AC) == 0) {
		/* trigger measurement */
		ret = i2c_smbus_write_byte_data(data->client, MAG3110_CTRL_REG1,
			data->ctrl_reg1 | MAG3110_CTRL_TM);
		if (ret < 0)
			return ret;
	}

	while (tries-- > 0) {
		ret = i2c_smbus_read_byte_data(data->client, MAG3110_STATUS);
		if (ret < 0)
			return ret;
		/* wait for data ready */
		if ((ret & MAG3110_STATUS_DRDY) == MAG3110_STATUS_DRDY)
			break;

		if (data->sleep_val <= 20)
			usleep_range(data->sleep_val * 250, data->sleep_val * 500);
		else
			msleep(20);
	}

	if (tries < 0) {
		dev_err(&data->client->dev, "data not ready\n");
		return -EIO;
	}

	return 0;
}