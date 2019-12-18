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
struct stm32_pwm {int /*<<< orphan*/  lock; } ;
struct pwm_state {int dummy; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stm32_pwm_apply (struct pwm_chip*,struct pwm_device*,struct pwm_state const*) ; 
 struct stm32_pwm* to_stm32_pwm_dev (struct pwm_chip*) ; 

__attribute__((used)) static int stm32_pwm_apply_locked(struct pwm_chip *chip, struct pwm_device *pwm,
				  const struct pwm_state *state)
{
	struct stm32_pwm *priv = to_stm32_pwm_dev(chip);
	int ret;

	/* protect common prescaler for all active channels */
	mutex_lock(&priv->lock);
	ret = stm32_pwm_apply(chip, pwm, state);
	mutex_unlock(&priv->lock);

	return ret;
}