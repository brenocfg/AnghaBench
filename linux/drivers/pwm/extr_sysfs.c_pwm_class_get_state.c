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
struct pwm_state {int dummy; } ;
struct pwm_export {int /*<<< orphan*/  lock; } ;
struct pwm_device {int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWMF_EXPORTED ; 
 struct pwm_export* child_to_pwm_export (struct device*) ; 
 struct device* device_find_child (struct device*,struct pwm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_unexport_match ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pwm_export *pwm_class_get_state(struct device *parent,
					      struct pwm_device *pwm,
					      struct pwm_state *state)
{
	struct device *child;
	struct pwm_export *export;

	if (!test_bit(PWMF_EXPORTED, &pwm->flags))
		return NULL;

	child = device_find_child(parent, pwm, pwm_unexport_match);
	if (!child)
		return NULL;

	export = child_to_pwm_export(child);
	put_device(child);	/* for device_find_child() */

	mutex_lock(&export->lock);
	pwm_get_state(pwm, state);

	return export;
}