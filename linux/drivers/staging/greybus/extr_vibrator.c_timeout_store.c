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
typedef  int /*<<< orphan*/  u16 ;
struct gb_vibrator_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct gb_vibrator_device* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int turn_off (struct gb_vibrator_device*) ; 
 int turn_on (struct gb_vibrator_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t timeout_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct gb_vibrator_device *vib = dev_get_drvdata(dev);
	unsigned long val;
	int retval;

	retval = kstrtoul(buf, 10, &val);
	if (retval < 0) {
		dev_err(dev, "could not parse timeout value %d\n", retval);
		return retval;
	}

	if (val)
		retval = turn_on(vib, (u16)val);
	else
		retval = turn_off(vib);
	if (retval)
		return retval;

	return count;
}