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
struct pem_data {int valid; int input_length; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/  fan_speed; scalar_t__ fans_supported; int /*<<< orphan*/  input_string; int /*<<< orphan*/  data_string; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pem_data* ERR_PTR (int) ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  PEM_CLEAR_INFO_FLAGS ; 
 int /*<<< orphan*/  PEM_READ_DATA_STRING ; 
 int /*<<< orphan*/  PEM_READ_FAN_SPEED ; 
 int /*<<< orphan*/  PEM_READ_INPUT_STRING ; 
 struct pem_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pem_read_block (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct pem_data *pem_update_device(struct device *dev)
{
	struct pem_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct pem_data *ret = data;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		int result;

		/* Read data string */
		result = pem_read_block(client, PEM_READ_DATA_STRING,
					data->data_string,
					sizeof(data->data_string));
		if (unlikely(result < 0)) {
			ret = ERR_PTR(result);
			goto abort;
		}

		/* Read input string */
		if (data->input_length) {
			result = pem_read_block(client, PEM_READ_INPUT_STRING,
						data->input_string,
						data->input_length);
			if (unlikely(result < 0)) {
				ret = ERR_PTR(result);
				goto abort;
			}
		}

		/* Read fan speeds */
		if (data->fans_supported) {
			result = pem_read_block(client, PEM_READ_FAN_SPEED,
						data->fan_speed,
						sizeof(data->fan_speed));
			if (unlikely(result < 0)) {
				ret = ERR_PTR(result);
				goto abort;
			}
		}

		i2c_smbus_write_byte(client, PEM_CLEAR_INFO_FLAGS);

		data->last_updated = jiffies;
		data->valid = 1;
	}
abort:
	mutex_unlock(&data->update_lock);
	return ret;
}