#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct srf08_data {unsigned int sensitivity; int /*<<< orphan*/  lock; TYPE_1__* chip_info; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int num_sensitivity_avail; unsigned int* sensitivity_avail; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SRF08_WRITE_MAX_GAIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t srf08_write_sensitivity(struct srf08_data *data,
							unsigned int val)
{
	struct i2c_client *client = data->client;
	int ret, i;
	u8 regval;

	if (!val)
		return -EINVAL;

	for (i = 0; i < data->chip_info->num_sensitivity_avail; i++)
		if (val && (val == data->chip_info->sensitivity_avail[i])) {
			regval = i;
			break;
		}

	if (i >= data->chip_info->num_sensitivity_avail)
		return -EINVAL;

	mutex_lock(&data->lock);

	ret = i2c_smbus_write_byte_data(client, SRF08_WRITE_MAX_GAIN, regval);
	if (ret < 0) {
		dev_err(&client->dev, "write_sensitivity - err: %d\n", ret);
		mutex_unlock(&data->lock);
		return ret;
	}

	data->sensitivity = val;

	mutex_unlock(&data->lock);

	return 0;
}