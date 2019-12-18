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
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct nct7802_data {int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SMARTFAN_EN (int /*<<< orphan*/ ) ; 
 int SMARTFAN_EN_SHIFT (int /*<<< orphan*/ ) ; 
 struct nct7802_data* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int sprintf (char*,char*,unsigned int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pwm_enable_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct nct7802_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	unsigned int reg, enabled;
	int ret;

	ret = regmap_read(data->regmap, REG_SMARTFAN_EN(sattr->index), &reg);
	if (ret < 0)
		return ret;
	enabled = reg >> SMARTFAN_EN_SHIFT(sattr->index) & 1;
	return sprintf(buf, "%u\n", enabled + 1);
}