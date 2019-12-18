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
struct TYPE_2__ {scalar_t__ power; int state; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int BL_CORE_FBBLANK ; 
 int BL_CORE_SUSPENDED ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int set_backlight_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_backlight_state (int) ; 

__attribute__((used)) static int bl_update_status(struct backlight_device *b)
{
	int ret = set_backlight_level(b->props.brightness);
	if (ret)
		return ret;

	set_backlight_state((b->props.power == FB_BLANK_UNBLANK)
		&&    !(b->props.state & BL_CORE_SUSPENDED)
		&&    !(b->props.state & BL_CORE_FBBLANK));
	return 0;
}