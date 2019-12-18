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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ab8500 {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_RTC ; 
 int /*<<< orphan*/  AB8500_SWITCH_OFF_STATUS ; 
 struct ab8500* dev_get_drvdata (struct device*) ; 
 int get_register_interruptible (struct ab8500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_switch_off_status(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int ret;
	u8 value;
	struct ab8500 *ab8500;

	ab8500 = dev_get_drvdata(dev);
	ret = get_register_interruptible(ab8500, AB8500_RTC,
		AB8500_SWITCH_OFF_STATUS, &value);
	if (ret < 0)
		return ret;
	return sprintf(buf, "%#x\n", value);
}