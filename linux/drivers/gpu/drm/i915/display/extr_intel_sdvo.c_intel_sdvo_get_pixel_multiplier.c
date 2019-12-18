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
struct drm_display_mode {int crtc_clock; } ;

/* Variables and functions */

__attribute__((used)) static int intel_sdvo_get_pixel_multiplier(const struct drm_display_mode *adjusted_mode)
{
	if (adjusted_mode->crtc_clock >= 100000)
		return 1;
	else if (adjusted_mode->crtc_clock >= 50000)
		return 2;
	else
		return 4;
}