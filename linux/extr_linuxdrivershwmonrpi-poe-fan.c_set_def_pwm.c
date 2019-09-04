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
struct rpi_poe_fan_ctx {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MAX_PWM ; 
 int __set_def_pwm (struct rpi_poe_fan_ctx*,unsigned long) ; 
 struct rpi_poe_fan_ctx* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t set_def_pwm(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct rpi_poe_fan_ctx *ctx = dev_get_drvdata(dev);
	unsigned long def_pwm;
	int ret;

	if (kstrtoul(buf, 10, &def_pwm) || def_pwm > MAX_PWM)
		return -EINVAL;

	ret = __set_def_pwm(ctx, def_pwm);
	if (ret)
		return ret;
	return count;
}