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
 int MODE_CLOCK_LOW ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status
imx6q_hdmi_mode_valid(struct drm_connector *con,
		      const struct drm_display_mode *mode)
{
	if (mode->clock < 13500)
		return MODE_CLOCK_LOW;
	/* FIXME: Hardware is capable of 266MHz, but setup data is missing. */
	if (mode->clock > 216000)
		return MODE_CLOCK_HIGH;

	return MODE_OK;
}