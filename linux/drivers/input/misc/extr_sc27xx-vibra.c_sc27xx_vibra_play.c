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
struct vibra_info {int /*<<< orphan*/  play_work; int /*<<< orphan*/  strength; } ;
struct input_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  weak_magnitude; } ;
struct TYPE_4__ {TYPE_1__ rumble; } ;
struct ff_effect {TYPE_2__ u; } ;

/* Variables and functions */
 struct vibra_info* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sc27xx_vibra_play(struct input_dev *input, void *data,
			     struct ff_effect *effect)
{
	struct vibra_info *info = input_get_drvdata(input);

	info->strength = effect->u.rumble.weak_magnitude;
	schedule_work(&info->play_work);

	return 0;
}