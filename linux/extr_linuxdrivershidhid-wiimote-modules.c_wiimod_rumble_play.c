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
struct TYPE_6__ {int cache_rumble; } ;
struct wiimote_data {int /*<<< orphan*/  rumble_worker; TYPE_3__ state; } ;
struct input_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ weak_magnitude; scalar_t__ strong_magnitude; } ;
struct TYPE_5__ {TYPE_1__ rumble; } ;
struct ff_effect {TYPE_2__ u; } ;
typedef  int __u8 ;

/* Variables and functions */
 struct wiimote_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wiimod_rumble_play(struct input_dev *dev, void *data,
			      struct ff_effect *eff)
{
	struct wiimote_data *wdata = input_get_drvdata(dev);
	__u8 value;

	/*
	 * The wiimote supports only a single rumble motor so if any magnitude
	 * is set to non-zero then we start the rumble motor. If both are set to
	 * zero, we stop the rumble motor.
	 */

	if (eff->u.rumble.strong_magnitude || eff->u.rumble.weak_magnitude)
		value = 1;
	else
		value = 0;

	/* Locking state.lock here might deadlock with input_event() calls.
	 * schedule_work acts as barrier. Merging multiple changes is fine. */
	wdata->state.cache_rumble = value;
	schedule_work(&wdata->rumble_worker);

	return 0;
}