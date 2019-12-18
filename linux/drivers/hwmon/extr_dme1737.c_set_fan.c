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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct dme1737_data {int* fan_min; int* fan_opt; int* fan_max; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DME1737_REG_FAN_MAX (int) ; 
 int /*<<< orphan*/  DME1737_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  DME1737_REG_FAN_OPT (int) ; 
 size_t EINVAL ; 
 int FAN_MAX_TO_REG (long) ; 
 void* FAN_TO_REG (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAN_TPC_FROM_REG (int) ; 
 int FAN_TYPE_TO_REG (long,int) ; 
#define  SYS_FAN_MAX 130 
#define  SYS_FAN_MIN 129 
#define  SYS_FAN_TYPE 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct dme1737_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,long) ; 
 int dme1737_read (struct dme1737_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme1737_write (struct dme1737_data*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_fan(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct dme1737_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	switch (fn) {
	case SYS_FAN_MIN:
		if (ix < 4) {
			data->fan_min[ix] = FAN_TO_REG(val, 0);
		} else {
			/* Refresh the cache */
			data->fan_opt[ix] = dme1737_read(data,
						DME1737_REG_FAN_OPT(ix));
			/* Modify the fan min value */
			data->fan_min[ix] = FAN_TO_REG(val,
					FAN_TPC_FROM_REG(data->fan_opt[ix]));
		}
		dme1737_write(data, DME1737_REG_FAN_MIN(ix),
			      data->fan_min[ix] & 0xff);
		dme1737_write(data, DME1737_REG_FAN_MIN(ix) + 1,
			      data->fan_min[ix] >> 8);
		break;
	case SYS_FAN_MAX:
		/* Only valid for fan[5-6] */
		data->fan_max[ix - 4] = FAN_MAX_TO_REG(val);
		dme1737_write(data, DME1737_REG_FAN_MAX(ix),
			      data->fan_max[ix - 4]);
		break;
	case SYS_FAN_TYPE:
		/* Only valid for fan[1-4] */
		if (!(val == 1 || val == 2 || val == 4)) {
			count = -EINVAL;
			dev_warn(dev,
				 "Fan type value %ld not supported. Choose one of 1, 2, or 4.\n",
				 val);
			goto exit;
		}
		data->fan_opt[ix] = FAN_TYPE_TO_REG(val, dme1737_read(data,
					DME1737_REG_FAN_OPT(ix)));
		dme1737_write(data, DME1737_REG_FAN_OPT(ix),
			      data->fan_opt[ix]);
		break;
	default:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}
exit:
	mutex_unlock(&data->update_lock);

	return count;
}