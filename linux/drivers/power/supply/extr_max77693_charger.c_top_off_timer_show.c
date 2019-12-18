#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct max77693_charger {TYPE_1__* max77693; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int CHG_CNFG_03_TOTIME_MASK ; 
 unsigned int CHG_CNFG_03_TOTIME_SHIFT ; 
 int /*<<< orphan*/  MAX77693_CHG_REG_CHG_CNFG_03 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct max77693_charger* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static ssize_t top_off_timer_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct max77693_charger *chg = dev_get_drvdata(dev);
	unsigned int data, val;
	int ret;

	ret = regmap_read(chg->max77693->regmap, MAX77693_CHG_REG_CHG_CNFG_03,
			&data);
	if (ret < 0)
		return ret;

	data &= CHG_CNFG_03_TOTIME_MASK;
	data >>= CHG_CNFG_03_TOTIME_SHIFT;

	val = data * 10;

	return scnprintf(buf, PAGE_SIZE, "%u\n", val);
}