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
struct power_supply {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bq2415x_device {scalar_t__ automode; int mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  BQ2415X_MODE_BOOST 132 
#define  BQ2415X_MODE_DEDICATED_CHARGER 131 
#define  BQ2415X_MODE_HOST_CHARGER 130 
#define  BQ2415X_MODE_NONE 129 
#define  BQ2415X_MODE_OFF 128 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 struct bq2415x_device* power_supply_get_drvdata (struct power_supply*) ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t bq2415x_sysfs_show_mode(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct power_supply *psy = dev_get_drvdata(dev);
	struct bq2415x_device *bq = power_supply_get_drvdata(psy);
	ssize_t ret = 0;

	if (bq->automode > 0)
		ret += sprintf(buf+ret, "auto (");

	switch (bq->mode) {
	case BQ2415X_MODE_OFF:
		ret += sprintf(buf+ret, "off");
		break;
	case BQ2415X_MODE_NONE:
		ret += sprintf(buf+ret, "none");
		break;
	case BQ2415X_MODE_HOST_CHARGER:
		ret += sprintf(buf+ret, "host");
		break;
	case BQ2415X_MODE_DEDICATED_CHARGER:
		ret += sprintf(buf+ret, "dedicated");
		break;
	case BQ2415X_MODE_BOOST:
		ret += sprintf(buf+ret, "boost");
		break;
	}

	if (bq->automode > 0)
		ret += sprintf(buf+ret, ")");

	ret += sprintf(buf+ret, "\n");
	return ret;
}