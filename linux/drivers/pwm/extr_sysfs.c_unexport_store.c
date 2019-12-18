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
struct pwm_chip {unsigned int npwm; int /*<<< orphan*/ * pwms; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 struct pwm_chip* dev_get_drvdata (struct device*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int pwm_unexport_child (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t unexport_store(struct device *parent,
			      struct device_attribute *attr,
			      const char *buf, size_t len)
{
	struct pwm_chip *chip = dev_get_drvdata(parent);
	unsigned int hwpwm;
	int ret;

	ret = kstrtouint(buf, 0, &hwpwm);
	if (ret < 0)
		return ret;

	if (hwpwm >= chip->npwm)
		return -ENODEV;

	ret = pwm_unexport_child(parent, &chip->pwms[hwpwm]);

	return ret ? : len;
}