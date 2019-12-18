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
struct TYPE_2__ {int /*<<< orphan*/  buttons; } ;
struct mousedev {scalar_t__ touch; scalar_t__ frac_dy; scalar_t__ frac_dx; scalar_t__ pkt_count; TYPE_1__ packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 struct mousedev* mousedev_mix ; 
 int /*<<< orphan*/  mousedev_notify_readers (struct mousedev*,TYPE_1__*) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tap_time ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mousedev_touchpad_touch(struct mousedev *mousedev, int value)
{
	if (!value) {
		if (mousedev->touch &&
		    time_before(jiffies,
				mousedev->touch + msecs_to_jiffies(tap_time))) {
			/*
			 * Toggle left button to emulate tap.
			 * We rely on the fact that mousedev_mix always has 0
			 * motion packet so we won't mess current position.
			 */
			set_bit(0, &mousedev->packet.buttons);
			set_bit(0, &mousedev_mix->packet.buttons);
			mousedev_notify_readers(mousedev, &mousedev_mix->packet);
			mousedev_notify_readers(mousedev_mix,
						&mousedev_mix->packet);
			clear_bit(0, &mousedev->packet.buttons);
			clear_bit(0, &mousedev_mix->packet.buttons);
		}
		mousedev->touch = mousedev->pkt_count = 0;
		mousedev->frac_dx = 0;
		mousedev->frac_dy = 0;

	} else if (!mousedev->touch)
		mousedev->touch = jiffies;
}