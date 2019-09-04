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
struct ltc4261_data {int valid; int* regs; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 struct ltc4261_data* ERR_PTR (int) ; 
 int HZ ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct ltc4261_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ltc4261_data *ltc4261_update_device(struct device *dev)
{
	struct ltc4261_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct ltc4261_data *ret = data;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ / 4) || !data->valid) {
		int i;

		/* Read registers -- 0x00 to 0x09 */
		for (i = 0; i < ARRAY_SIZE(data->regs); i++) {
			int val;

			val = i2c_smbus_read_byte_data(client, i);
			if (unlikely(val < 0)) {
				dev_dbg(dev,
					"Failed to read ADC value: error %d\n",
					val);
				ret = ERR_PTR(val);
				data->valid = 0;
				goto abort;
			}
			data->regs[i] = val;
		}
		data->last_updated = jiffies;
		data->valid = 1;
	}
abort:
	mutex_unlock(&data->update_lock);
	return ret;
}