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
struct pwm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pwm_apply_state (struct pwm_device*,struct pwm_state*) ; 

__attribute__((used)) static int pwm_class_apply_state(struct pwm_export *export,
				 struct pwm_device *pwm,
				 struct pwm_state *state)
{
	int ret = pwm_apply_state(pwm, state);

	/* release lock taken in pwm_class_get_state */
	mutex_unlock(&export->lock);

	return ret;
}