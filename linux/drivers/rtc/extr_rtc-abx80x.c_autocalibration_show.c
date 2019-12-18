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
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int abx80x_rtc_get_autocalibration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t autocalibration_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	int autocalibration = 0;

	autocalibration = abx80x_rtc_get_autocalibration(dev->parent);
	if (autocalibration < 0) {
		dev_err(dev, "Failed to read RTC autocalibration\n");
		sprintf(buf, "0\n");
		return autocalibration;
	}

	return sprintf(buf, "%d\n", autocalibration);
}