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
struct regmap {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 
 struct regmap* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_power_reg (int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int ltc2945_val_to_reg (struct device*,int,unsigned long) ; 
 int regmap_bulk_write (struct regmap*,int,int*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ltc2945_value_store(struct device *dev,
				   struct device_attribute *da,
				   const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct regmap *regmap = dev_get_drvdata(dev);
	u8 reg = attr->index;
	unsigned long val;
	u8 regbuf[3];
	int num_regs;
	int regval;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	/* convert to register value, then clamp and write result */
	regval = ltc2945_val_to_reg(dev, reg, val);
	if (is_power_reg(reg)) {
		regval = clamp_val(regval, 0, 0xffffff);
		regbuf[0] = regval >> 16;
		regbuf[1] = (regval >> 8) & 0xff;
		regbuf[2] = regval;
		num_regs = 3;
	} else {
		regval = clamp_val(regval, 0, 0xfff) << 4;
		regbuf[0] = regval >> 8;
		regbuf[1] = regval & 0xff;
		num_regs = 2;
	}
	ret = regmap_bulk_write(regmap, reg, regbuf, num_regs);
	return ret < 0 ? ret : count;
}