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
typedef  int u8 ;
struct w83627ehf_data {unsigned long* fan_min; int* fan_div; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * REG_FAN_MIN; int /*<<< orphan*/  last_updated; int /*<<< orphan*/  (* fan_from_reg_min ) (int,int) ;int /*<<< orphan*/  has_fan_div; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct w83627ehf_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_from_reg (int) ; 
 int /*<<< orphan*/  jiffies ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int /*<<< orphan*/  w83627ehf_write_fan_div_common (struct device*,struct w83627ehf_data*,int) ; 
 int /*<<< orphan*/  w83627ehf_write_value (struct w83627ehf_data*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static ssize_t
store_fan_min(struct device *dev, struct device_attribute *attr,
	      const char *buf, size_t count)
{
	struct w83627ehf_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	unsigned long val;
	int err;
	unsigned int reg;
	u8 new_div;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	mutex_lock(&data->update_lock);
	if (!data->has_fan_div) {
		/*
		 * Only NCT6776F for now, so we know that this is a 13 bit
		 * register
		 */
		if (!val) {
			val = 0xff1f;
		} else {
			if (val > 1350000U)
				val = 135000U;
			val = 1350000U / val;
			val = (val & 0x1f) | ((val << 3) & 0xff00);
		}
		data->fan_min[nr] = val;
		goto done;	/* Leave fan divider alone */
	}
	if (!val) {
		/* No min limit, alarm disabled */
		data->fan_min[nr] = 255;
		new_div = data->fan_div[nr]; /* No change */
		dev_info(dev, "fan%u low limit and alarm disabled\n", nr + 1);
	} else if ((reg = 1350000U / val) >= 128 * 255) {
		/*
		 * Speed below this value cannot possibly be represented,
		 * even with the highest divider (128)
		 */
		data->fan_min[nr] = 254;
		new_div = 7; /* 128 == (1 << 7) */
		dev_warn(dev,
			 "fan%u low limit %lu below minimum %u, set to minimum\n",
			 nr + 1, val, data->fan_from_reg_min(254, 7));
	} else if (!reg) {
		/*
		 * Speed above this value cannot possibly be represented,
		 * even with the lowest divider (1)
		 */
		data->fan_min[nr] = 1;
		new_div = 0; /* 1 == (1 << 0) */
		dev_warn(dev,
			 "fan%u low limit %lu above maximum %u, set to maximum\n",
			 nr + 1, val, data->fan_from_reg_min(1, 0));
	} else {
		/*
		 * Automatically pick the best divider, i.e. the one such
		 * that the min limit will correspond to a register value
		 * in the 96..192 range
		 */
		new_div = 0;
		while (reg > 192 && new_div < 7) {
			reg >>= 1;
			new_div++;
		}
		data->fan_min[nr] = reg;
	}

	/*
	 * Write both the fan clock divider (if it changed) and the new
	 * fan min (unconditionally)
	 */
	if (new_div != data->fan_div[nr]) {
		dev_dbg(dev, "fan%u clock divider changed from %u to %u\n",
			nr + 1, div_from_reg(data->fan_div[nr]),
			div_from_reg(new_div));
		data->fan_div[nr] = new_div;
		w83627ehf_write_fan_div_common(dev, data, nr);
		/* Give the chip time to sample a new speed value */
		data->last_updated = jiffies;
	}
done:
	w83627ehf_write_value(data, data->REG_FAN_MIN[nr],
			      data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	return count;
}