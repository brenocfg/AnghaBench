#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int dummy; } ;
struct TYPE_5__ {int strong_magnitude; } ;
struct TYPE_6__ {TYPE_2__ rumble; } ;
struct ff_effect {int direction; TYPE_3__ u; } ;
struct arizona_haptics {int intensity; int /*<<< orphan*/  work; struct arizona* arizona; } ;
struct TYPE_4__ {scalar_t__ hap_act; } ;
struct arizona {TYPE_1__ pdata; int /*<<< orphan*/  dev; int /*<<< orphan*/  dapm; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct arizona_haptics* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arizona_haptics_play(struct input_dev *input, void *data,
				struct ff_effect *effect)
{
	struct arizona_haptics *haptics = input_get_drvdata(input);
	struct arizona *arizona = haptics->arizona;

	if (!arizona->dapm) {
		dev_err(arizona->dev, "No DAPM context\n");
		return -EBUSY;
	}

	if (effect->u.rumble.strong_magnitude) {
		/* Scale the magnitude into the range the device supports */
		if (arizona->pdata.hap_act) {
			haptics->intensity =
				effect->u.rumble.strong_magnitude >> 9;
			if (effect->direction < 0x8000)
				haptics->intensity += 0x7f;
		} else {
			haptics->intensity =
				effect->u.rumble.strong_magnitude >> 8;
		}
	} else {
		haptics->intensity = 0;
	}

	schedule_work(&haptics->work);

	return 0;
}