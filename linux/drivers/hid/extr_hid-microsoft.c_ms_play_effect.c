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
typedef  int u32 ;
struct ms_data {int strong; int weak; int /*<<< orphan*/  ff_worker; } ;
struct input_dev {int dummy; } ;
struct hid_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ weak_magnitude; scalar_t__ strong_magnitude; } ;
struct TYPE_4__ {TYPE_1__ rumble; } ;
struct ff_effect {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ FF_RUMBLE ; 
 int U16_MAX ; 
 struct ms_data* hid_get_drvdata (struct hid_device*) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ms_play_effect(struct input_dev *dev, void *data,
			  struct ff_effect *effect)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct ms_data *ms = hid_get_drvdata(hid);

	if (effect->type != FF_RUMBLE)
		return 0;

	/*
	 * Magnitude is 0..100 so scale the 16-bit input here
	 */
	ms->strong = ((u32) effect->u.rumble.strong_magnitude * 100) / U16_MAX;
	ms->weak = ((u32) effect->u.rumble.weak_magnitude * 100) / U16_MAX;

	schedule_work(&ms->ff_worker);
	return 0;
}