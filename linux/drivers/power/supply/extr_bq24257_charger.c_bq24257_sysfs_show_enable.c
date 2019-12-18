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
struct power_supply {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
struct bq24257_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  F_HZ_MODE ; 
 int /*<<< orphan*/  F_SYSOFF ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int bq24257_field_read (struct bq24257_device*,int /*<<< orphan*/ ) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 struct bq24257_device* power_supply_get_drvdata (struct power_supply*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t bq24257_sysfs_show_enable(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct power_supply *psy = dev_get_drvdata(dev);
	struct bq24257_device *bq = power_supply_get_drvdata(psy);
	int ret;

	if (strcmp(attr->attr.name, "high_impedance_enable") == 0)
		ret = bq24257_field_read(bq, F_HZ_MODE);
	else if (strcmp(attr->attr.name, "sysoff_enable") == 0)
		ret = bq24257_field_read(bq, F_SYSOFF);
	else
		return -EINVAL;

	if (ret < 0)
		return ret;

	return scnprintf(buf, PAGE_SIZE, "%d\n", ret);
}