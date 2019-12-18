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
typedef  void* u8 ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct dme1737_data {int /*<<< orphan*/  update_lock; void** zone_abs; void** pwm_freq; void** zone_low; void** zone_hyst; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DME1737_REG_PWM_FREQ (int) ; 
 int /*<<< orphan*/  DME1737_REG_ZONE_ABS (int) ; 
 int /*<<< orphan*/  DME1737_REG_ZONE_HYST (int) ; 
 int /*<<< orphan*/  DME1737_REG_ZONE_LOW (int) ; 
#define  SYS_ZONE_AUTO_POINT1_TEMP 131 
#define  SYS_ZONE_AUTO_POINT1_TEMP_HYST 130 
#define  SYS_ZONE_AUTO_POINT2_TEMP 129 
#define  SYS_ZONE_AUTO_POINT3_TEMP 128 
 int TEMP_FROM_REG (void*,int) ; 
 void* TEMP_HYST_TO_REG (int,long,int,void*) ; 
 void* TEMP_RANGE_TO_REG (long,void*) ; 
 void* TEMP_TO_REG (long) ; 
 long clamp_val (long,int,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct dme1737_data* dev_get_drvdata (struct device*) ; 
 void* dme1737_read (struct dme1737_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme1737_write (struct dme1737_data*,int /*<<< orphan*/ ,void*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_zone(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct dme1737_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	long val;
	int temp;
	int err;
	u8 reg;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	switch (fn) {
	case SYS_ZONE_AUTO_POINT1_TEMP_HYST:
		/* Refresh the cache */
		data->zone_low[ix] = dme1737_read(data,
						  DME1737_REG_ZONE_LOW(ix));
		/* Modify the temp hyst value */
		temp = TEMP_FROM_REG(data->zone_low[ix], 8);
		reg = dme1737_read(data, DME1737_REG_ZONE_HYST(ix == 2));
		data->zone_hyst[ix == 2] = TEMP_HYST_TO_REG(temp, val, ix, reg);
		dme1737_write(data, DME1737_REG_ZONE_HYST(ix == 2),
			      data->zone_hyst[ix == 2]);
		break;
	case SYS_ZONE_AUTO_POINT1_TEMP:
		data->zone_low[ix] = TEMP_TO_REG(val);
		dme1737_write(data, DME1737_REG_ZONE_LOW(ix),
			      data->zone_low[ix]);
		break;
	case SYS_ZONE_AUTO_POINT2_TEMP:
		/* Refresh the cache */
		data->zone_low[ix] = dme1737_read(data,
						  DME1737_REG_ZONE_LOW(ix));
		/*
		 * Modify the temp range value (which is stored in the upper
		 * nibble of the pwm_freq register)
		 */
		temp = TEMP_FROM_REG(data->zone_low[ix], 8);
		val = clamp_val(val, temp, temp + 80000);
		reg = dme1737_read(data, DME1737_REG_PWM_FREQ(ix));
		data->pwm_freq[ix] = TEMP_RANGE_TO_REG(val - temp, reg);
		dme1737_write(data, DME1737_REG_PWM_FREQ(ix),
			      data->pwm_freq[ix]);
		break;
	case SYS_ZONE_AUTO_POINT3_TEMP:
		data->zone_abs[ix] = TEMP_TO_REG(val);
		dme1737_write(data, DME1737_REG_ZONE_ABS(ix),
			      data->zone_abs[ix]);
		break;
	default:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}
	mutex_unlock(&data->update_lock);

	return count;
}