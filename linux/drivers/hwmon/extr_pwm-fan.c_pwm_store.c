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
struct pwm_fan_ctx {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MAX_PWM ; 
 int __set_pwm (struct pwm_fan_ctx*,unsigned long) ; 
 struct pwm_fan_ctx* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  pwm_fan_update_state (struct pwm_fan_ctx*,unsigned long) ; 

__attribute__((used)) static ssize_t pwm_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct pwm_fan_ctx *ctx = dev_get_drvdata(dev);
	unsigned long pwm;
	int ret;

	if (kstrtoul(buf, 10, &pwm) || pwm > MAX_PWM)
		return -EINVAL;

	ret = __set_pwm(ctx, pwm);
	if (ret)
		return ret;

	pwm_fan_update_state(ctx, pwm);
	return count;
}