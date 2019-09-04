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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ms_ht_dev {size_t res_index; TYPE_1__* client; int /*<<< orphan*/  lock; } ;
typedef  int s64 ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MS_SENSORS_HT_T_CONVERSION_START ; 
 int /*<<< orphan*/  MS_SENSORS_NO_READ_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ms_sensors_convert_and_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ms_sensors_crc_valid (int) ; 
 int /*<<< orphan*/ * ms_sensors_ht_t_conversion_time ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ms_sensors_ht_read_temperature(struct ms_ht_dev *dev_data,
				   s32 *temperature)
{
	int ret;
	u32 adc;
	u16 delay;

	mutex_lock(&dev_data->lock);
	delay = ms_sensors_ht_t_conversion_time[dev_data->res_index];
	ret = ms_sensors_convert_and_read(dev_data->client,
					  MS_SENSORS_HT_T_CONVERSION_START,
					  MS_SENSORS_NO_READ_CMD,
					  delay, &adc);
	mutex_unlock(&dev_data->lock);
	if (ret)
		return ret;

	if (!ms_sensors_crc_valid(adc)) {
		dev_err(&dev_data->client->dev,
			"Temperature read crc check error\n");
		return -ENODEV;
	}

	/* Temperature algorithm */
	*temperature = (((s64)(adc >> 8) * 175720) >> 16) - 46850;

	return 0;
}