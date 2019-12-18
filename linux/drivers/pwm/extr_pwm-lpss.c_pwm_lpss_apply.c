#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pwm_state {int /*<<< orphan*/  period; int /*<<< orphan*/  duty_cycle; scalar_t__ enabled; } ;
struct pwm_lpss_chip {TYPE_1__* info; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int bypass; } ;

/* Variables and functions */
 int PWM_ENABLE ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 scalar_t__ pwm_is_enabled (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_lpss_cond_enable (struct pwm_device*,int) ; 
 int pwm_lpss_is_updating (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_lpss_prepare (struct pwm_lpss_chip*,struct pwm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pwm_lpss_read (struct pwm_device*) ; 
 int pwm_lpss_wait_for_update (struct pwm_device*) ; 
 int /*<<< orphan*/  pwm_lpss_write (struct pwm_device*,int) ; 
 struct pwm_lpss_chip* to_lpwm (struct pwm_chip*) ; 

__attribute__((used)) static int pwm_lpss_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			  const struct pwm_state *state)
{
	struct pwm_lpss_chip *lpwm = to_lpwm(chip);
	int ret;

	if (state->enabled) {
		if (!pwm_is_enabled(pwm)) {
			pm_runtime_get_sync(chip->dev);
			ret = pwm_lpss_is_updating(pwm);
			if (ret) {
				pm_runtime_put(chip->dev);
				return ret;
			}
			pwm_lpss_prepare(lpwm, pwm, state->duty_cycle, state->period);
			pwm_lpss_cond_enable(pwm, lpwm->info->bypass == false);
			ret = pwm_lpss_wait_for_update(pwm);
			if (ret) {
				pm_runtime_put(chip->dev);
				return ret;
			}
			pwm_lpss_cond_enable(pwm, lpwm->info->bypass == true);
		} else {
			ret = pwm_lpss_is_updating(pwm);
			if (ret)
				return ret;
			pwm_lpss_prepare(lpwm, pwm, state->duty_cycle, state->period);
			return pwm_lpss_wait_for_update(pwm);
		}
	} else if (pwm_is_enabled(pwm)) {
		pwm_lpss_write(pwm, pwm_lpss_read(pwm) & ~PWM_ENABLE);
		pm_runtime_put(chip->dev);
	}

	return 0;
}