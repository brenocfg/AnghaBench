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
typedef  int ulong ;
struct sensor_device_attribute_2 {int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int* enh_acoustics; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t EINVAL ; 
 unsigned char REG_ENHANCE_ACOUSTICS1 ; 
 unsigned char REG_ENHANCE_ACOUSTICS2 ; 
 int /*<<< orphan*/  ad7475_st_map ; 
 struct adt7475_data* dev_get_drvdata (struct device*) ; 
 int find_closest_descending (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,unsigned char,int) ; 
 scalar_t__ kstrtoul (char const*,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_st_store(struct device *dev,
			     struct device_attribute *attr, const char *buf,
			     size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct adt7475_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned char reg;
	int shift, idx;
	ulong val;

	if (kstrtoul(buf, 10, &val))
		return -EINVAL;

	switch (sattr->index) {
	case 0:
		reg = REG_ENHANCE_ACOUSTICS1;
		shift = 0;
		idx = 0;
		break;
	case 1:
		reg = REG_ENHANCE_ACOUSTICS2;
		shift = 0;
		idx = 1;
		break;
	case 2:
	default:
		reg = REG_ENHANCE_ACOUSTICS2;
		shift = 4;
		idx = 1;
		break;
	}

	if (val > 0) {
		val = find_closest_descending(val, ad7475_st_map,
					      ARRAY_SIZE(ad7475_st_map));
		val |= 0x8;
	}

	mutex_lock(&data->lock);

	data->enh_acoustics[idx] &= ~(0xf << shift);
	data->enh_acoustics[idx] |= (val << shift);

	i2c_smbus_write_byte_data(client, reg, data->enh_acoustics[idx]);

	mutex_unlock(&data->lock);

	return count;
}