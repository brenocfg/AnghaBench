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
struct srf08_data {int range_mm; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SRF08_CMD_RANGING_CM ; 
 int /*<<< orphan*/  SRF08_READ_ECHO_1_HIGH ; 
 int /*<<< orphan*/  SRF08_READ_SW_REVISION ; 
 int /*<<< orphan*/  SRF08_WRITE_COMMAND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int srf08_read_ranging(struct srf08_data *data)
{
	struct i2c_client *client = data->client;
	int ret, i;
	int waittime;

	mutex_lock(&data->lock);

	ret = i2c_smbus_write_byte_data(data->client,
			SRF08_WRITE_COMMAND, SRF08_CMD_RANGING_CM);
	if (ret < 0) {
		dev_err(&client->dev, "write command - err: %d\n", ret);
		mutex_unlock(&data->lock);
		return ret;
	}

	/*
	 * we read here until a correct version number shows up as
	 * suggested by the documentation
	 *
	 * with an ultrasonic speed of 343 m/s and a roundtrip of it
	 * sleep the expected duration and try to read from the device
	 * if nothing useful is read try it in a shorter grid
	 *
	 * polling for not more than 20 ms should be enough
	 */
	waittime = 1 + data->range_mm / 172;
	msleep(waittime);
	for (i = 0; i < 4; i++) {
		ret = i2c_smbus_read_byte_data(data->client,
						SRF08_READ_SW_REVISION);

		/* check if a valid version number is read */
		if (ret < 255 && ret > 0)
			break;
		msleep(5);
	}

	if (ret >= 255 || ret <= 0) {
		dev_err(&client->dev, "device not ready\n");
		mutex_unlock(&data->lock);
		return -EIO;
	}

	ret = i2c_smbus_read_word_swapped(data->client,
						SRF08_READ_ECHO_1_HIGH);
	if (ret < 0) {
		dev_err(&client->dev, "cannot read distance: ret=%d\n", ret);
		mutex_unlock(&data->lock);
		return ret;
	}

	mutex_unlock(&data->lock);

	return ret;
}