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
typedef  int u8 ;
struct srf08_data {unsigned int range_mm; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SRF08_WRITE_RANGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t srf08_write_range_mm(struct srf08_data *data, unsigned int val)
{
	int ret;
	struct i2c_client *client = data->client;
	unsigned int mod;
	u8 regval;

	ret = val / 43 - 1;
	mod = val % 43;

	if (mod || (ret < 0) || (ret > 255))
		return -EINVAL;

	regval = ret;

	mutex_lock(&data->lock);

	ret = i2c_smbus_write_byte_data(client, SRF08_WRITE_RANGE, regval);
	if (ret < 0) {
		dev_err(&client->dev, "write_range - err: %d\n", ret);
		mutex_unlock(&data->lock);
		return ret;
	}

	data->range_mm = val;

	mutex_unlock(&data->lock);

	return 0;
}