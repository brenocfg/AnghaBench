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
struct radeon_device {TYPE_2__* asic; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* fan_ctrl_set_mode ) (struct radeon_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ dpm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FDO_PWM_MODE_STATIC ; 
 struct radeon_device* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int,int*) ; 
 int /*<<< orphan*/  stub1 (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t radeon_hwmon_set_pwm1_enable(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf,
					    size_t count)
{
	struct radeon_device *rdev = dev_get_drvdata(dev);
	int err;
	int value;

	if(!rdev->asic->dpm.fan_ctrl_set_mode)
		return -EINVAL;

	err = kstrtoint(buf, 10, &value);
	if (err)
		return err;

	switch (value) {
	case 1: /* manual, percent-based */
		rdev->asic->dpm.fan_ctrl_set_mode(rdev, FDO_PWM_MODE_STATIC);
		break;
	default: /* disable */
		rdev->asic->dpm.fan_ctrl_set_mode(rdev, 0);
		break;
	}

	return count;
}