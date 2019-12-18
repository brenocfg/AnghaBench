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
struct omap_dss_device {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_INTERLACE_HALVE_V ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int EINVAL ; 
#define  VENC_MODE_NTSC 129 
#define  VENC_MODE_PAL 128 
 int /*<<< orphan*/  drm_mode_copy (struct drm_display_mode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 int /*<<< orphan*/  omap_dss_ntsc_mode ; 
 int /*<<< orphan*/  omap_dss_pal_mode ; 
 int venc_get_videomode (struct drm_display_mode*) ; 

__attribute__((used)) static int venc_check_timings(struct omap_dss_device *dssdev,
			      struct drm_display_mode *mode)
{
	DSSDBG("venc_check_timings\n");

	switch (venc_get_videomode(mode)) {
	case VENC_MODE_PAL:
		drm_mode_copy(mode, &omap_dss_pal_mode);
		break;

	case VENC_MODE_NTSC:
		drm_mode_copy(mode, &omap_dss_ntsc_mode);
		break;

	default:
		return -EINVAL;
	}

	drm_mode_set_crtcinfo(mode, CRTC_INTERLACE_HALVE_V);
	drm_mode_set_name(mode);
	return 0;
}