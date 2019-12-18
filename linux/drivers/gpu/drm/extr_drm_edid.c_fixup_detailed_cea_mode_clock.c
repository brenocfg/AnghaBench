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
typedef  size_t u8 ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,char const*,size_t,int,int) ; 
 scalar_t__ abs (int) ; 
 int cea_mode_alternate_clock (struct drm_display_mode const*) ; 
 size_t drm_match_cea_mode_clock_tolerance (struct drm_display_mode*,int) ; 
 size_t drm_match_hdmi_mode_clock_tolerance (struct drm_display_mode*,int) ; 
 scalar_t__ drm_valid_cea_vic (size_t) ; 
 scalar_t__ drm_valid_hdmi_vic (size_t) ; 
 struct drm_display_mode* edid_4k_modes ; 
 struct drm_display_mode* edid_cea_modes ; 
 int hdmi_mode_alternate_clock (struct drm_display_mode const*) ; 

__attribute__((used)) static void fixup_detailed_cea_mode_clock(struct drm_display_mode *mode)
{
	const struct drm_display_mode *cea_mode;
	int clock1, clock2, clock;
	u8 vic;
	const char *type;

	/*
	 * allow 5kHz clock difference either way to account for
	 * the 10kHz clock resolution limit of detailed timings.
	 */
	vic = drm_match_cea_mode_clock_tolerance(mode, 5);
	if (drm_valid_cea_vic(vic)) {
		type = "CEA";
		cea_mode = &edid_cea_modes[vic];
		clock1 = cea_mode->clock;
		clock2 = cea_mode_alternate_clock(cea_mode);
	} else {
		vic = drm_match_hdmi_mode_clock_tolerance(mode, 5);
		if (drm_valid_hdmi_vic(vic)) {
			type = "HDMI";
			cea_mode = &edid_4k_modes[vic];
			clock1 = cea_mode->clock;
			clock2 = hdmi_mode_alternate_clock(cea_mode);
		} else {
			return;
		}
	}

	/* pick whichever is closest */
	if (abs(mode->clock - clock1) < abs(mode->clock - clock2))
		clock = clock1;
	else
		clock = clock2;

	if (mode->clock == clock)
		return;

	DRM_DEBUG("detailed mode matches %s VIC %d, adjusting clock %d -> %d\n",
		  type, vic, mode->clock, clock);
	mode->clock = clock;
}