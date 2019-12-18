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
typedef  int u8 ;
struct drm_display_mode {int vtotal; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; } ;
struct TYPE_2__ {int vtotal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 TYPE_1__* edid_cea_modes ; 

__attribute__((used)) static bool
cea_mode_alternate_timings(u8 vic, struct drm_display_mode *mode)
{
	/*
	 * For certain VICs the spec allows the vertical
	 * front porch to vary by one or two lines.
	 *
	 * cea_modes[] stores the variant with the shortest
	 * vertical front porch. We can adjust the mode to
	 * get the other variants by simply increasing the
	 * vertical front porch length.
	 */
	BUILD_BUG_ON(edid_cea_modes[8].vtotal != 262 ||
		     edid_cea_modes[9].vtotal != 262 ||
		     edid_cea_modes[12].vtotal != 262 ||
		     edid_cea_modes[13].vtotal != 262 ||
		     edid_cea_modes[23].vtotal != 312 ||
		     edid_cea_modes[24].vtotal != 312 ||
		     edid_cea_modes[27].vtotal != 312 ||
		     edid_cea_modes[28].vtotal != 312);

	if (((vic == 8 || vic == 9 ||
	      vic == 12 || vic == 13) && mode->vtotal < 263) ||
	    ((vic == 23 || vic == 24 ||
	      vic == 27 || vic == 28) && mode->vtotal < 314)) {
		mode->vsync_start++;
		mode->vsync_end++;
		mode->vtotal++;

		return true;
	}

	return false;
}