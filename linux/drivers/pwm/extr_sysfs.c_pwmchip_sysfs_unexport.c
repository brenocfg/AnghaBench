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
struct pwm_device {int /*<<< orphan*/  flags; } ;
struct pwm_chip {unsigned int npwm; struct pwm_device* pwms; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWMF_EXPORTED ; 
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  pwm_class ; 
 int /*<<< orphan*/  pwm_unexport_child (struct device*,struct pwm_device*) ; 
 int /*<<< orphan*/  pwmchip_sysfs_match ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pwmchip_sysfs_unexport(struct pwm_chip *chip)
{
	struct device *parent;
	unsigned int i;

	parent = class_find_device(&pwm_class, NULL, chip,
				   pwmchip_sysfs_match);
	if (!parent)
		return;

	for (i = 0; i < chip->npwm; i++) {
		struct pwm_device *pwm = &chip->pwms[i];

		if (test_bit(PWMF_EXPORTED, &pwm->flags))
			pwm_unexport_child(parent, pwm);
	}

	put_device(parent);
	device_unregister(parent);
}