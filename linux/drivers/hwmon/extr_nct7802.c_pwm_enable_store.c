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
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct nct7802_data {int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_SMARTFAN_EN (int /*<<< orphan*/ ) ; 
 int SMARTFAN_EN_SHIFT (int /*<<< orphan*/ ) ; 
 struct nct7802_data* dev_get_drvdata (struct device*) ; 
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pwm_enable_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct nct7802_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	u8 val;
	int ret;

	ret = kstrtou8(buf, 0, &val);
	if (ret < 0)
		return ret;
	if (val < 1 || val > 2)
		return -EINVAL;
	ret = regmap_update_bits(data->regmap, REG_SMARTFAN_EN(sattr->index),
				 1 << SMARTFAN_EN_SHIFT(sattr->index),
				 (val - 1) << SMARTFAN_EN_SHIFT(sattr->index));
	return ret ? : count;
}