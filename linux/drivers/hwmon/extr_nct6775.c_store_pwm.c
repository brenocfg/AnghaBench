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
struct sensor_device_attribute_2 {int nr; int index; } ;
struct nct6775_data {int** pwm; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * REG_TEMP_SEL; int /*<<< orphan*/ ** REG_PWM; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long clamp_val (unsigned long,int,int) ; 
 struct nct6775_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
store_pwm(struct device *dev, struct device_attribute *attr, const char *buf,
	  size_t count)
{
	struct nct6775_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int nr = sattr->nr;
	int index = sattr->index;
	unsigned long val;
	int minval[7] = { 0, 1, 1, data->pwm[2][nr], 0, 0, 0 };
	int maxval[7]
	  = { 255, 255, data->pwm[3][nr] ? : 255, 255, 255, 255, 255 };
	int err;
	u8 reg;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;
	val = clamp_val(val, minval[index], maxval[index]);

	mutex_lock(&data->update_lock);
	data->pwm[index][nr] = val;
	nct6775_write_value(data, data->REG_PWM[index][nr], val);
	if (index == 2)	{ /* floor: disable if val == 0 */
		reg = nct6775_read_value(data, data->REG_TEMP_SEL[nr]);
		reg &= 0x7f;
		if (val)
			reg |= 0x80;
		nct6775_write_value(data, data->REG_TEMP_SEL[nr], reg);
	}
	mutex_unlock(&data->update_lock);
	return count;
}