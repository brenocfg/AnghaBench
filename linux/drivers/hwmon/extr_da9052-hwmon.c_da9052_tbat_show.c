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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct da9052_hwmon {int /*<<< orphan*/  da9052; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int da9052_adc_read_temp (int /*<<< orphan*/ ) ; 
 struct da9052_hwmon* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t da9052_tbat_show(struct device *dev,
				struct device_attribute *devattr, char *buf)
{
	struct da9052_hwmon *hwmon = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", da9052_adc_read_temp(hwmon->da9052));
}