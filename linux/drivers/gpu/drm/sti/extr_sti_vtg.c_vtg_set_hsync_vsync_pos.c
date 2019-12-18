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
typedef  int u32 ;
struct sti_vtg_sync_params {long hsync; int vsync_line_top; int vsync_off_top; int vsync_line_bot; int vsync_off_bot; } ;
struct drm_display_mode {long htotal; long hsync_end; long hsync_start; int vsync_end; int vsync_start; int vtotal; } ;

/* Variables and functions */

__attribute__((used)) static void vtg_set_hsync_vsync_pos(struct sti_vtg_sync_params *sync,
				    int delay,
				    const struct drm_display_mode *mode)
{
	long clocksperline, start, stop;
	u32 risesync_top, fallsync_top;
	u32 risesync_offs_top, fallsync_offs_top;

	clocksperline = mode->htotal;

	/* Get the hsync position */
	start = 0;
	stop = mode->hsync_end - mode->hsync_start;

	start += delay;
	stop  += delay;

	if (start < 0)
		start += clocksperline;
	else if (start >= clocksperline)
		start -= clocksperline;

	if (stop < 0)
		stop += clocksperline;
	else if (stop >= clocksperline)
		stop -= clocksperline;

	sync->hsync = (stop << 16) | start;

	/* Get the vsync position */
	if (delay >= 0) {
		risesync_top = 1;
		fallsync_top = risesync_top;
		fallsync_top += mode->vsync_end - mode->vsync_start;

		fallsync_offs_top = (u32)delay;
		risesync_offs_top = (u32)delay;
	} else {
		risesync_top = mode->vtotal;
		fallsync_top = mode->vsync_end - mode->vsync_start;

		fallsync_offs_top = clocksperline + delay;
		risesync_offs_top = clocksperline + delay;
	}

	sync->vsync_line_top = (fallsync_top << 16) | risesync_top;
	sync->vsync_off_top = (fallsync_offs_top << 16) | risesync_offs_top;

	/* Only progressive supported for now */
	sync->vsync_line_bot = sync->vsync_line_top;
	sync->vsync_off_bot = sync->vsync_off_top;
}