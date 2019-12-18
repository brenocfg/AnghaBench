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
struct w83627hf_data {unsigned long* sens; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int* BIT_SCFG1 ; 
 int* BIT_SCFG2 ; 
#define  W83781D_DEFAULT_BETA 128 
 int /*<<< orphan*/  W83781D_REG_SCFG1 ; 
 int /*<<< orphan*/  W83781D_REG_SCFG2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,long) ; 
 struct w83627hf_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int const) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83627hf_read_value (struct w83627hf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627hf_write_value (struct w83627hf_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
temp_type_store(struct device *dev, struct device_attribute *devattr,
		const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(devattr)->index;
	struct w83627hf_data *data = dev_get_drvdata(dev);
	unsigned long val;
	u32 tmp;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	switch (val) {
	case 1:		/* PII/Celeron diode */
		tmp = w83627hf_read_value(data, W83781D_REG_SCFG1);
		w83627hf_write_value(data, W83781D_REG_SCFG1,
				    tmp | BIT_SCFG1[nr]);
		tmp = w83627hf_read_value(data, W83781D_REG_SCFG2);
		w83627hf_write_value(data, W83781D_REG_SCFG2,
				    tmp | BIT_SCFG2[nr]);
		data->sens[nr] = val;
		break;
	case 2:		/* 3904 */
		tmp = w83627hf_read_value(data, W83781D_REG_SCFG1);
		w83627hf_write_value(data, W83781D_REG_SCFG1,
				    tmp | BIT_SCFG1[nr]);
		tmp = w83627hf_read_value(data, W83781D_REG_SCFG2);
		w83627hf_write_value(data, W83781D_REG_SCFG2,
				    tmp & ~BIT_SCFG2[nr]);
		data->sens[nr] = val;
		break;
	case W83781D_DEFAULT_BETA:
		dev_warn(dev, "Sensor type %d is deprecated, please use 4 "
			 "instead\n", W83781D_DEFAULT_BETA);
		/* fall through */
	case 4:		/* thermistor */
		tmp = w83627hf_read_value(data, W83781D_REG_SCFG1);
		w83627hf_write_value(data, W83781D_REG_SCFG1,
				    tmp & ~BIT_SCFG1[nr]);
		data->sens[nr] = val;
		break;
	default:
		dev_err(dev,
		       "Invalid sensor type %ld; must be 1, 2, or 4\n",
		       (long) val);
		break;
	}

	mutex_unlock(&data->update_lock);
	return count;
}