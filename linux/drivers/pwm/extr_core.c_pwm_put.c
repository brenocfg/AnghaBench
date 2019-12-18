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
struct pwm_device {TYPE_2__* chip; int /*<<< orphan*/ * label; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* free ) (TYPE_2__*,struct pwm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PWMF_REQUESTED ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  pwm_lock ; 
 int /*<<< orphan*/  pwm_set_chip_data (struct pwm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct pwm_device*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pwm_put(struct pwm_device *pwm)
{
	if (!pwm)
		return;

	mutex_lock(&pwm_lock);

	if (!test_and_clear_bit(PWMF_REQUESTED, &pwm->flags)) {
		pr_warn("PWM device already freed\n");
		goto out;
	}

	if (pwm->chip->ops->free)
		pwm->chip->ops->free(pwm->chip, pwm);

	pwm_set_chip_data(pwm, NULL);
	pwm->label = NULL;

	module_put(pwm->chip->ops->owner);
out:
	mutex_unlock(&pwm_lock);
}