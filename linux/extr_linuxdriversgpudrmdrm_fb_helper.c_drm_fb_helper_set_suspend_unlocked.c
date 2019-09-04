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
struct drm_fb_helper {TYPE_1__* fbdev; int /*<<< orphan*/  resume_work; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_trylock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  fb_set_suspend (TYPE_1__*,int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void drm_fb_helper_set_suspend_unlocked(struct drm_fb_helper *fb_helper,
					bool suspend)
{
	if (!fb_helper || !fb_helper->fbdev)
		return;

	/* make sure there's no pending/ongoing resume */
	flush_work(&fb_helper->resume_work);

	if (suspend) {
		if (fb_helper->fbdev->state != FBINFO_STATE_RUNNING)
			return;

		console_lock();

	} else {
		if (fb_helper->fbdev->state == FBINFO_STATE_RUNNING)
			return;

		if (!console_trylock()) {
			schedule_work(&fb_helper->resume_work);
			return;
		}
	}

	fb_set_suspend(fb_helper->fbdev, suspend);
	console_unlock();
}