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
typedef  int u64 ;
struct pwm_args {scalar_t__ period; } ;
struct max77693_haptic {int magnitude; unsigned int pwm_duty; int /*<<< orphan*/  work; int /*<<< orphan*/  pwm_dev; } ;
struct input_dev {int dummy; } ;
struct TYPE_4__ {int strong_magnitude; int weak_magnitude; } ;
struct TYPE_3__ {TYPE_2__ rumble; } ;
struct ff_effect {TYPE_1__ u; } ;

/* Variables and functions */
 int MAX_MAGNITUDE_SHIFT ; 
 struct max77693_haptic* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  pwm_get_args (int /*<<< orphan*/ ,struct pwm_args*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max77693_haptic_play_effect(struct input_dev *dev, void *data,
				       struct ff_effect *effect)
{
	struct max77693_haptic *haptic = input_get_drvdata(dev);
	struct pwm_args pargs;
	u64 period_mag_multi;

	haptic->magnitude = effect->u.rumble.strong_magnitude;
	if (!haptic->magnitude)
		haptic->magnitude = effect->u.rumble.weak_magnitude;

	/*
	 * The magnitude comes from force-feedback interface.
	 * The formula to convert magnitude to pwm_duty as follows:
	 * - pwm_duty = (magnitude * pwm_period) / MAX_MAGNITUDE(0xFFFF)
	 */
	pwm_get_args(haptic->pwm_dev, &pargs);
	period_mag_multi = (u64)pargs.period * haptic->magnitude;
	haptic->pwm_duty = (unsigned int)(period_mag_multi >>
						MAX_MAGNITUDE_SHIFT);

	schedule_work(&haptic->work);

	return 0;
}