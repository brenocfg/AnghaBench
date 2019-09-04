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
struct drm_display_mode {unsigned int clock; int vrefresh; int vdisplay; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 

__attribute__((used)) static unsigned int
cea_mode_alternate_clock(const struct drm_display_mode *cea_mode)
{
	unsigned int clock = cea_mode->clock;

	if (cea_mode->vrefresh % 6 != 0)
		return clock;

	/*
	 * edid_cea_modes contains the 59.94Hz
	 * variant for 240 and 480 line modes,
	 * and the 60Hz variant otherwise.
	 */
	if (cea_mode->vdisplay == 240 || cea_mode->vdisplay == 480)
		clock = DIV_ROUND_CLOSEST(clock * 1001, 1000);
	else
		clock = DIV_ROUND_CLOSEST(clock * 1000, 1001);

	return clock;
}