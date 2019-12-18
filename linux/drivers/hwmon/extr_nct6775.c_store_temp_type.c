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
struct sensor_device_attribute {int index; } ;
struct nct6775_data {unsigned long* temp_type; int DIODE_MASK; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  REG_DIODE; int /*<<< orphan*/  REG_VBAT; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
 struct nct6775_data* nct6775_update_device (struct device*) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
store_temp_type(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct nct6775_data *data = nct6775_update_device(dev);
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	int nr = sattr->index;
	unsigned long val;
	int err;
	u8 vbat, diode, vbit, dbit;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	if (val != 1 && val != 3 && val != 4)
		return -EINVAL;

	mutex_lock(&data->update_lock);

	data->temp_type[nr] = val;
	vbit = 0x02 << nr;
	dbit = data->DIODE_MASK << nr;
	vbat = nct6775_read_value(data, data->REG_VBAT) & ~vbit;
	diode = nct6775_read_value(data, data->REG_DIODE) & ~dbit;
	switch (val) {
	case 1:	/* CPU diode (diode, current mode) */
		vbat |= vbit;
		diode |= dbit;
		break;
	case 3: /* diode, voltage mode */
		vbat |= dbit;
		break;
	case 4:	/* thermistor */
		break;
	}
	nct6775_write_value(data, data->REG_VBAT, vbat);
	nct6775_write_value(data, data->REG_DIODE, diode);

	mutex_unlock(&data->update_lock);
	return count;
}