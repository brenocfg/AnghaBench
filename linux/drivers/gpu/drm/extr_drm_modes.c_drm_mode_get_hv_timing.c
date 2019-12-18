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
struct drm_display_mode {int crtc_hdisplay; int crtc_vdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_STEREO_DOUBLE_ONLY ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 

void drm_mode_get_hv_timing(const struct drm_display_mode *mode,
			    int *hdisplay, int *vdisplay)
{
	struct drm_display_mode adjusted = *mode;

	drm_mode_set_crtcinfo(&adjusted, CRTC_STEREO_DOUBLE_ONLY);
	*hdisplay = adjusted.crtc_hdisplay;
	*vdisplay = adjusted.crtc_vdisplay;
}