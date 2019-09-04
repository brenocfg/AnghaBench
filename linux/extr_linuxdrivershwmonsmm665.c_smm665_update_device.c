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
struct smm665_data {int valid; int faults; int* adc; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct smm665_data* ERR_PTR (int) ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  SMM665_MISC8_STATUS1 ; 
 int SMM665_NUM_ADC ; 
 struct smm665_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smm665_read16 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int smm665_read_adc (struct smm665_data*,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct smm665_data *smm665_update_device(struct device *dev)
{
	struct smm665_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	struct smm665_data *ret = data;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		int i, val;

		/*
		 * read status registers
		 */
		val = smm665_read16(client, SMM665_MISC8_STATUS1);
		if (unlikely(val < 0)) {
			ret = ERR_PTR(val);
			goto abort;
		}
		data->faults = val;

		/* Read adc registers */
		for (i = 0; i < SMM665_NUM_ADC; i++) {
			val = smm665_read_adc(data, i);
			if (unlikely(val < 0)) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->adc[i] = val;
		}
		data->last_updated = jiffies;
		data->valid = 1;
	}
abort:
	mutex_unlock(&data->update_lock);
	return ret;
}