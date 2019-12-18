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
typedef  scalar_t__ u32 ;
struct phy_device {int dummy; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MII_INTSRC ; 
 int MII_INTSRC_TEMP_ERR ; 
 int MII_INTSRC_UV_ERR ; 
 struct phy_device* dev_get_drvdata (struct device*) ; 
 int hwmon_in ; 
 scalar_t__ hwmon_in_lcrit_alarm ; 
 int hwmon_temp ; 
 scalar_t__ hwmon_temp_crit_alarm ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tja11xx_hwmon_read(struct device *dev,
			      enum hwmon_sensor_types type,
			      u32 attr, int channel, long *value)
{
	struct phy_device *phydev = dev_get_drvdata(dev);
	int ret;

	if (type == hwmon_in && attr == hwmon_in_lcrit_alarm) {
		ret = phy_read(phydev, MII_INTSRC);
		if (ret < 0)
			return ret;

		*value = !!(ret & MII_INTSRC_TEMP_ERR);
		return 0;
	}

	if (type == hwmon_temp && attr == hwmon_temp_crit_alarm) {
		ret = phy_read(phydev, MII_INTSRC);
		if (ret < 0)
			return ret;

		*value = !!(ret & MII_INTSRC_UV_ERR);
		return 0;
	}

	return -EOPNOTSUPP;
}