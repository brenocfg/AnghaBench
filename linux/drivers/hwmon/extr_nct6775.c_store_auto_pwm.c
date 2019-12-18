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
struct nct6775_data {int auto_pwm_num; int kind; unsigned long** auto_pwm; int CRITICAL_PWM_ENABLE_MASK; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * REG_CRITICAL_PWM_ENABLE; int /*<<< orphan*/ * REG_CRITICAL_PWM; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NCT6775_AUTO_PWM (struct nct6775_data*,int,int) ; 
 int /*<<< orphan*/ * NCT6775_REG_CRITICAL_ENAB ; 
 struct nct6775_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
#define  nct6106 139 
#define  nct6116 138 
#define  nct6775 137 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int) ; 
#define  nct6776 136 
#define  nct6779 135 
#define  nct6791 134 
#define  nct6792 133 
#define  nct6793 132 
#define  nct6795 131 
#define  nct6796 130 
#define  nct6797 129 
#define  nct6798 128 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
store_auto_pwm(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	struct nct6775_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int nr = sattr->nr;
	int point = sattr->index;
	unsigned long val;
	int err;
	u8 reg;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;
	if (val > 255)
		return -EINVAL;

	if (point == data->auto_pwm_num) {
		if (data->kind != nct6775 && !val)
			return -EINVAL;
		if (data->kind != nct6779 && val)
			val = 0xff;
	}

	mutex_lock(&data->update_lock);
	data->auto_pwm[nr][point] = val;
	if (point < data->auto_pwm_num) {
		nct6775_write_value(data,
				    NCT6775_AUTO_PWM(data, nr, point),
				    data->auto_pwm[nr][point]);
	} else {
		switch (data->kind) {
		case nct6775:
			/* disable if needed (pwm == 0) */
			reg = nct6775_read_value(data,
						 NCT6775_REG_CRITICAL_ENAB[nr]);
			if (val)
				reg |= 0x02;
			else
				reg &= ~0x02;
			nct6775_write_value(data, NCT6775_REG_CRITICAL_ENAB[nr],
					    reg);
			break;
		case nct6776:
			break; /* always enabled, nothing to do */
		case nct6106:
		case nct6116:
		case nct6779:
		case nct6791:
		case nct6792:
		case nct6793:
		case nct6795:
		case nct6796:
		case nct6797:
		case nct6798:
			nct6775_write_value(data, data->REG_CRITICAL_PWM[nr],
					    val);
			reg = nct6775_read_value(data,
					data->REG_CRITICAL_PWM_ENABLE[nr]);
			if (val == 255)
				reg &= ~data->CRITICAL_PWM_ENABLE_MASK;
			else
				reg |= data->CRITICAL_PWM_ENABLE_MASK;
			nct6775_write_value(data,
					    data->REG_CRITICAL_PWM_ENABLE[nr],
					    reg);
			break;
		}
	}
	mutex_unlock(&data->update_lock);
	return count;
}