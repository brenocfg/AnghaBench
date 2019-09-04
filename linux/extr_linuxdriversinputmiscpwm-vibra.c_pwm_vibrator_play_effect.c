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
struct pwm_vibrator {int /*<<< orphan*/  play_work; scalar_t__ level; } ;
struct input_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ weak_magnitude; scalar_t__ strong_magnitude; } ;
struct TYPE_4__ {TYPE_1__ rumble; } ;
struct ff_effect {TYPE_2__ u; } ;

/* Variables and functions */
 struct pwm_vibrator* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwm_vibrator_play_effect(struct input_dev *dev, void *data,
				    struct ff_effect *effect)
{
	struct pwm_vibrator *vibrator = input_get_drvdata(dev);

	vibrator->level = effect->u.rumble.strong_magnitude;
	if (!vibrator->level)
		vibrator->level = effect->u.rumble.weak_magnitude;

	schedule_work(&vibrator->play_work);

	return 0;
}