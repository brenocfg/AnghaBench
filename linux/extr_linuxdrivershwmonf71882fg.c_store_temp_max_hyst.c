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
struct f71882fg_data {int* temp_high; int* temp_hyst; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  F71882FG_REG_TEMP_HIGH (int) ; 
 int /*<<< orphan*/  F71882FG_REG_TEMP_HYST (int) ; 
 long clamp_val (long,int,int) ; 
 struct f71882fg_data* dev_get_drvdata (struct device*) ; 
 void* f71882fg_read8 (struct f71882fg_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f71882fg_write8 (struct f71882fg_data*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_temp_max_hyst(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	struct f71882fg_data *data = dev_get_drvdata(dev);
	int err, nr = to_sensor_dev_attr_2(devattr)->index;
	ssize_t ret = count;
	u8 reg;
	long val;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	val /= 1000;

	mutex_lock(&data->update_lock);

	/* convert abs to relative and check */
	data->temp_high[nr] = f71882fg_read8(data, F71882FG_REG_TEMP_HIGH(nr));
	val = clamp_val(val, data->temp_high[nr] - 15, data->temp_high[nr]);
	val = data->temp_high[nr] - val;

	/* convert value to register contents */
	reg = f71882fg_read8(data, F71882FG_REG_TEMP_HYST(nr / 2));
	if (nr & 1)
		reg = (reg & 0x0f) | (val << 4);
	else
		reg = (reg & 0xf0) | val;
	f71882fg_write8(data, F71882FG_REG_TEMP_HYST(nr / 2), reg);
	data->temp_hyst[nr / 2] = reg;

	mutex_unlock(&data->update_lock);
	return ret;
}