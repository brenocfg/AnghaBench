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
struct drm_display_mode {int clock; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_CLOCK_HIGH ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status
sun8i_dw_hdmi_mode_valid_h6(struct drm_connector *connector,
			    const struct drm_display_mode *mode)
{
	/*
	 * Controller support maximum of 594 MHz, which correlates to
	 * 4K@60Hz 4:4:4 or RGB. However, for frequencies greater than
	 * 340 MHz scrambling has to be enabled. Because scrambling is
	 * not yet implemented, just limit to 340 MHz for now.
	 */
	if (mode->clock > 340000)
		return MODE_CLOCK_HIGH;

	return MODE_OK;
}