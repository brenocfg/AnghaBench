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
struct sharp_panel {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 unsigned int drm_mode_vrefresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void sharp_wait_frames(struct sharp_panel *sharp, unsigned int frames)
{
	unsigned int refresh = drm_mode_vrefresh(sharp->mode);

	if (WARN_ON(frames > refresh))
		return;

	msleep(1000 / (refresh / frames));
}