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
struct regmap {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int EINVAL ; 
#define  LTC4222_ADIN1 133 
#define  LTC4222_ADIN2 132 
#define  LTC4222_SENSE1 131 
#define  LTC4222_SENSE2 130 
#define  LTC4222_SOURCE1 129 
#define  LTC4222_SOURCE2 128 
 struct regmap* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (struct regmap*,int,int*,int) ; 

__attribute__((used)) static int ltc4222_get_value(struct device *dev, u8 reg)
{
	struct regmap *regmap = dev_get_drvdata(dev);
	unsigned int val;
	u8 buf[2];
	int ret;

	ret = regmap_bulk_read(regmap, reg, buf, 2);
	if (ret < 0)
		return ret;

	val = ((buf[0] << 8) + buf[1]) >> 6;

	switch (reg) {
	case LTC4222_ADIN1:
	case LTC4222_ADIN2:
		/* 1.25 mV resolution. Convert to mV. */
		val = DIV_ROUND_CLOSEST(val * 5, 4);
		break;
	case LTC4222_SOURCE1:
	case LTC4222_SOURCE2:
		/* 31.25 mV resolution. Convert to mV. */
		val = DIV_ROUND_CLOSEST(val * 125, 4);
		break;
	case LTC4222_SENSE1:
	case LTC4222_SENSE2:
		/*
		 * 62.5 uV resolution. Convert to current as measured with
		 * an 1 mOhm sense resistor, in mA. If a different sense
		 * resistor is installed, calculate the actual current by
		 * dividing the reported current by the sense resistor value
		 * in mOhm.
		 */
		val = DIV_ROUND_CLOSEST(val * 125, 2);
		break;
	default:
		return -EINVAL;
	}
	return val;
}