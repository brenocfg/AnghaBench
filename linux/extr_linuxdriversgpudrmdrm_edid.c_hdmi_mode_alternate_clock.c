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
struct drm_display_mode {int vdisplay; int hdisplay; unsigned int clock; } ;

/* Variables and functions */
 unsigned int cea_mode_alternate_clock (struct drm_display_mode const*) ; 

__attribute__((used)) static unsigned int
hdmi_mode_alternate_clock(const struct drm_display_mode *hdmi_mode)
{
	if (hdmi_mode->vdisplay == 4096 && hdmi_mode->hdisplay == 2160)
		return hdmi_mode->clock;

	return cea_mode_alternate_clock(hdmi_mode);
}