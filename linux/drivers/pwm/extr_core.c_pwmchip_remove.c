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
struct pwm_chip {unsigned int npwm; int /*<<< orphan*/  list; struct pwm_device* pwms; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EBUSY ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWMF_REQUESTED ; 
 int /*<<< orphan*/  free_pwms (struct pwm_chip*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwmchip_remove (struct pwm_chip*) ; 
 int /*<<< orphan*/  pwm_lock ; 
 int /*<<< orphan*/  pwmchip_sysfs_unexport (struct pwm_chip*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int pwmchip_remove(struct pwm_chip *chip)
{
	unsigned int i;
	int ret = 0;

	pwmchip_sysfs_unexport(chip);

	mutex_lock(&pwm_lock);

	for (i = 0; i < chip->npwm; i++) {
		struct pwm_device *pwm = &chip->pwms[i];

		if (test_bit(PWMF_REQUESTED, &pwm->flags)) {
			ret = -EBUSY;
			goto out;
		}
	}

	list_del_init(&chip->list);

	if (IS_ENABLED(CONFIG_OF))
		of_pwmchip_remove(chip);

	free_pwms(chip);

out:
	mutex_unlock(&pwm_lock);
	return ret;
}