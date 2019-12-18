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
struct pwm_state {int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;
struct pwm_export {TYPE_1__ suspend; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {struct pwm_device* pwms; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pwm_chip* dev_get_drvdata (struct device*) ; 
 int pwm_class_apply_state (struct pwm_export*,struct pwm_device*,struct pwm_state*) ; 
 struct pwm_export* pwm_class_get_state (struct device*,struct pwm_device*,struct pwm_state*) ; 

__attribute__((used)) static int pwm_class_resume_npwm(struct device *parent, unsigned int npwm)
{
	struct pwm_chip *chip = dev_get_drvdata(parent);
	unsigned int i;
	int ret = 0;

	for (i = 0; i < npwm; i++) {
		struct pwm_device *pwm = &chip->pwms[i];
		struct pwm_state state;
		struct pwm_export *export;

		export = pwm_class_get_state(parent, pwm, &state);
		if (!export)
			continue;

		state.enabled = export->suspend.enabled;
		ret = pwm_class_apply_state(export, pwm, &state);
		if (ret < 0)
			break;
	}

	return ret;
}