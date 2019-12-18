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
struct fb_info {struct da8xx_fb_par* par; } ;
struct da8xx_fb_par {scalar_t__ vsync_flag; int /*<<< orphan*/  vsync_timeout; int /*<<< orphan*/  vsync_wait; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fb_wait_for_vsync(struct fb_info *info)
{
	struct da8xx_fb_par *par = info->par;
	int ret;

	/*
	 * Set flag to 0 and wait for isr to set to 1. It would seem there is a
	 * race condition here where the ISR could have occurred just before or
	 * just after this set. But since we are just coarsely waiting for
	 * a frame to complete then that's OK. i.e. if the frame completed
	 * just before this code executed then we have to wait another full
	 * frame time but there is no way to avoid such a situation. On the
	 * other hand if the frame completed just after then we don't need
	 * to wait long at all. Either way we are guaranteed to return to the
	 * user immediately after a frame completion which is all that is
	 * required.
	 */
	par->vsync_flag = 0;
	ret = wait_event_interruptible_timeout(par->vsync_wait,
					       par->vsync_flag != 0,
					       par->vsync_timeout);
	if (ret < 0)
		return ret;
	if (ret == 0)
		return -ETIMEDOUT;

	return 0;
}