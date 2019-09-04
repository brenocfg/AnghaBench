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
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct hih6130 {int valid; int /*<<< orphan*/  lock; scalar_t__ last_update; int /*<<< orphan*/  temperature; int /*<<< orphan*/  humidity; int /*<<< orphan*/  write_length; struct i2c_client* client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct hih6130* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hih6130_rh_ticks_to_per_cent_mille (int) ; 
 int /*<<< orphan*/  hih6130_temp_ticks_to_millicelsius (int) ; 
 int i2c_master_send (struct i2c_client*,unsigned char*,int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int hih6130_update_measurements(struct device *dev)
{
	struct hih6130 *hih6130 = dev_get_drvdata(dev);
	struct i2c_client *client = hih6130->client;
	int ret = 0;
	int t;
	unsigned char tmp[4];
	struct i2c_msg msgs[1] = {
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 4,
			.buf = tmp,
		}
	};

	mutex_lock(&hih6130->lock);

	/*
	 * While the measurement can be completed in ~40ms the sensor takes
	 * much longer to react to a change in external conditions. How quickly
	 * it reacts depends on airflow and other factors outwith our control.
	 * The datasheet specifies maximum 'Response time' for humidity at 8s
	 * and temperature at 30s under specified conditions.
	 * We therefore choose to only read the sensor at most once per second.
	 * This trades off pointless activity polling the sensor much faster
	 * than it can react against better response times in conditions more
	 * favourable than specified in the datasheet.
	 */
	if (time_after(jiffies, hih6130->last_update + HZ) || !hih6130->valid) {

		/*
		 * Write to slave address to request a measurement.
		 * According with the datasheet it should be with no data, but
		 * for systems with I2C bus drivers that do not allow zero
		 * length packets we write one dummy byte to allow sensor
		 * measurements on them.
		 */
		tmp[0] = 0;
		ret = i2c_master_send(client, tmp, hih6130->write_length);
		if (ret < 0)
			goto out;

		/* measurement cycle time is ~36.65msec */
		msleep(40);

		ret = i2c_transfer(client->adapter, msgs, 1);
		if (ret < 0)
			goto out;

		if ((tmp[0] & 0xC0) != 0) {
			dev_err(&client->dev, "Error while reading measurement result\n");
			ret = -EIO;
			goto out;
		}

		t = (tmp[0] << 8) + tmp[1];
		hih6130->humidity = hih6130_rh_ticks_to_per_cent_mille(t);

		t = (tmp[2] << 8) + tmp[3];
		hih6130->temperature = hih6130_temp_ticks_to_millicelsius(t);

		hih6130->last_update = jiffies;
		hih6130->valid = true;
	}
out:
	mutex_unlock(&hih6130->lock);

	return ret >= 0 ? 0 : ret;
}