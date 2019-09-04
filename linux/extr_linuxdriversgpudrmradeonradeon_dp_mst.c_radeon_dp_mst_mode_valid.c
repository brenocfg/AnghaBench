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
struct drm_display_mode {int clock; int flags; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLCLK ; 
 int MODE_CLOCK_LOW ; 
 int MODE_H_ILLEGAL ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status
radeon_dp_mst_mode_valid(struct drm_connector *connector,
			struct drm_display_mode *mode)
{
	/* TODO - validate mode against available PBN for link */
	if (mode->clock < 10000)
		return MODE_CLOCK_LOW;

	if (mode->flags & DRM_MODE_FLAG_DBLCLK)
		return MODE_H_ILLEGAL;

	return MODE_OK;
}