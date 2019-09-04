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
typedef  int /*<<< orphan*/  u8 ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LTC4260_ADIN 130 
#define  LTC4260_SENSE 129 
#define  LTC4260_SOURCE 128 
 struct regmap* dev_get_drvdata (struct device*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ltc4260_get_value(struct device *dev, u8 reg)
{
	struct regmap *regmap = dev_get_drvdata(dev);
	unsigned int val;
	int ret;

	ret = regmap_read(regmap, reg, &val);
	if (ret < 0)
		return ret;

	switch (reg) {
	case LTC4260_ADIN:
		/* 10 mV resolution. Convert to mV. */
		val = val * 10;
		break;
	case LTC4260_SOURCE:
		/* 400 mV resolution. Convert to mV. */
		val = val * 400;
		break;
	case LTC4260_SENSE:
		/*
		 * 300 uV resolution. Convert to current as measured with
		 * an 1 mOhm sense resistor, in mA. If a different sense
		 * resistor is installed, calculate the actual current by
		 * dividing the reported current by the sense resistor value
		 * in mOhm.
		 */
		val = val * 300;
		break;
	default:
		return -EINVAL;
	}

	return val;
}