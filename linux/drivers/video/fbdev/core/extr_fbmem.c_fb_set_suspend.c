#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fb_info {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  FBINFO_STATE_SUSPENDED ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  fbcon_resumed (struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_suspended (struct fb_info*) ; 

void fb_set_suspend(struct fb_info *info, int state)
{
	WARN_CONSOLE_UNLOCKED();

	if (state) {
		fbcon_suspended(info);
		info->state = FBINFO_STATE_SUSPENDED;
	} else {
		info->state = FBINFO_STATE_RUNNING;
		fbcon_resumed(info);
	}
}