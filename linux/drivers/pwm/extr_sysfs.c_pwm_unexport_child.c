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
struct pwm_device {int /*<<< orphan*/  hwpwm; int /*<<< orphan*/  flags; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  PWMF_EXPORTED ; 
 struct device* device_find_child (struct device*,struct pwm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  pwm_put (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_unexport_match ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwm_unexport_child(struct device *parent, struct pwm_device *pwm)
{
	struct device *child;
	char *pwm_prop[2];

	if (!test_and_clear_bit(PWMF_EXPORTED, &pwm->flags))
		return -ENODEV;

	child = device_find_child(parent, pwm, pwm_unexport_match);
	if (!child)
		return -ENODEV;

	pwm_prop[0] = kasprintf(GFP_KERNEL, "UNEXPORT=pwm%u", pwm->hwpwm);
	pwm_prop[1] = NULL;
	kobject_uevent_env(&parent->kobj, KOBJ_CHANGE, pwm_prop);
	kfree(pwm_prop[0]);

	/* for device_find_child() */
	put_device(child);
	device_unregister(child);
	pwm_put(pwm);

	return 0;
}