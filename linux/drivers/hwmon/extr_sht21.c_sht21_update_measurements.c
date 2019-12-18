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
struct sht21 {int valid; int /*<<< orphan*/  lock; scalar_t__ last_update; int /*<<< orphan*/  humidity; int /*<<< orphan*/  temperature; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SHT21_TRIG_RH_MEASUREMENT_HM ; 
 int /*<<< orphan*/  SHT21_TRIG_T_MEASUREMENT_HM ; 
 struct sht21* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sht21_rh_ticks_to_per_cent_mille (int) ; 
 int /*<<< orphan*/  sht21_temp_ticks_to_millicelsius (int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sht21_update_measurements(struct device *dev)
{
	int ret = 0;
	struct sht21 *sht21 = dev_get_drvdata(dev);
	struct i2c_client *client = sht21->client;

	mutex_lock(&sht21->lock);
	/*
	 * Data sheet 2.4:
	 * SHT2x should not be active for more than 10% of the time - e.g.
	 * maximum two measurements per second at 12bit accuracy shall be made.
	 */
	if (time_after(jiffies, sht21->last_update + HZ / 2) || !sht21->valid) {
		ret = i2c_smbus_read_word_swapped(client,
						  SHT21_TRIG_T_MEASUREMENT_HM);
		if (ret < 0)
			goto out;
		sht21->temperature = sht21_temp_ticks_to_millicelsius(ret);
		ret = i2c_smbus_read_word_swapped(client,
						  SHT21_TRIG_RH_MEASUREMENT_HM);
		if (ret < 0)
			goto out;
		sht21->humidity = sht21_rh_ticks_to_per_cent_mille(ret);
		sht21->last_update = jiffies;
		sht21->valid = 1;
	}
out:
	mutex_unlock(&sht21->lock);

	return ret >= 0 ? 0 : ret;
}