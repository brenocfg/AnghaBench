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
struct bq2415x_device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum bq2415x_command { ____Placeholder_bq2415x_command } bq2415x_command ;

/* Variables and functions */
 int BQ2415X_CHARGE_TERMINATION_STATUS ; 
 int BQ2415X_HIGH_IMPEDANCE_STATUS ; 
 int BQ2415X_OTG_PIN_STATUS ; 
 int BQ2415X_STAT_PIN_STATUS ; 
 int EINVAL ; 
 int bq2415x_exec_command (struct bq2415x_device*,int) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 struct bq2415x_device* power_supply_get_drvdata (struct power_supply*) ; 
 int sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t bq2415x_sysfs_show_enable(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct power_supply *psy = dev_get_drvdata(dev);
	struct bq2415x_device *bq = power_supply_get_drvdata(psy);
	enum bq2415x_command command;
	int ret;

	if (strcmp(attr->attr.name, "charge_termination_enable") == 0)
		command = BQ2415X_CHARGE_TERMINATION_STATUS;
	else if (strcmp(attr->attr.name, "high_impedance_enable") == 0)
		command = BQ2415X_HIGH_IMPEDANCE_STATUS;
	else if (strcmp(attr->attr.name, "otg_pin_enable") == 0)
		command = BQ2415X_OTG_PIN_STATUS;
	else if (strcmp(attr->attr.name, "stat_pin_enable") == 0)
		command = BQ2415X_STAT_PIN_STATUS;
	else
		return -EINVAL;

	ret = bq2415x_exec_command(bq, command);
	if (ret < 0)
		return ret;
	return sprintf(buf, "%d\n", ret);
}