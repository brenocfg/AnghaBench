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
struct input_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ strong_magnitude; scalar_t__ weak_magnitude; } ;
struct TYPE_3__ {TYPE_2__ rumble; } ;
struct ff_effect {TYPE_1__ u; } ;
struct drv260x_data {scalar_t__ magnitude; int /*<<< orphan*/  work; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV260X_LRA_NO_CAL_MODE ; 
 struct drv260x_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drv260x_haptics_play(struct input_dev *input, void *data,
				struct ff_effect *effect)
{
	struct drv260x_data *haptics = input_get_drvdata(input);

	haptics->mode = DRV260X_LRA_NO_CAL_MODE;

	if (effect->u.rumble.strong_magnitude > 0)
		haptics->magnitude = effect->u.rumble.strong_magnitude;
	else if (effect->u.rumble.weak_magnitude > 0)
		haptics->magnitude = effect->u.rumble.weak_magnitude;
	else
		haptics->magnitude = 0;

	schedule_work(&haptics->work);

	return 0;
}