#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_device {TYPE_2__* asic; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int (* get_fan_speed_percent ) (struct radeon_device*,int*) ;} ;
struct TYPE_4__ {TYPE_1__ dpm; } ;

/* Variables and functions */
 struct radeon_device* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 
 int stub1 (struct radeon_device*,int*) ; 

__attribute__((used)) static ssize_t radeon_hwmon_get_pwm1(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct radeon_device *rdev = dev_get_drvdata(dev);
	int err;
	u32 speed;

	err = rdev->asic->dpm.get_fan_speed_percent(rdev, &speed);
	if (err)
		return err;

	speed = (speed * 255) / 100;

	return sprintf(buf, "%i\n", speed);
}