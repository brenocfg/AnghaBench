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
struct drm_mode_modeinfo {scalar_t__ clock; scalar_t__ vrefresh; int flags; int type; int /*<<< orphan*/  name; int /*<<< orphan*/  vscan; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hskew; int /*<<< orphan*/  htotal; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  hdisplay; } ;
struct drm_display_mode {scalar_t__ clock; scalar_t__ vrefresh; int flags; int type; scalar_t__ status; int /*<<< orphan*/  picture_aspect_ratio; scalar_t__* name; int /*<<< orphan*/  vscan; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hskew; int /*<<< orphan*/  htotal; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  hdisplay; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_INTERLACE_HALVE_V ; 
 int DRM_DISPLAY_MODE_LEN ; 
#define  DRM_MODE_FLAG_PIC_AR_16_9 132 
#define  DRM_MODE_FLAG_PIC_AR_256_135 131 
#define  DRM_MODE_FLAG_PIC_AR_4_3 130 
#define  DRM_MODE_FLAG_PIC_AR_64_27 129 
 int DRM_MODE_FLAG_PIC_AR_MASK ; 
#define  DRM_MODE_FLAG_PIC_AR_NONE 128 
 int DRM_MODE_TYPE_ALL ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  HDMI_PICTURE_ASPECT_16_9 ; 
 int /*<<< orphan*/  HDMI_PICTURE_ASPECT_256_135 ; 
 int /*<<< orphan*/  HDMI_PICTURE_ASPECT_4_3 ; 
 int /*<<< orphan*/  HDMI_PICTURE_ASPECT_64_27 ; 
 int /*<<< orphan*/  HDMI_PICTURE_ASPECT_NONE ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ MODE_OK ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_mode_validate_driver (struct drm_device*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

int drm_mode_convert_umode(struct drm_device *dev,
			   struct drm_display_mode *out,
			   const struct drm_mode_modeinfo *in)
{
	if (in->clock > INT_MAX || in->vrefresh > INT_MAX)
		return -ERANGE;

	out->clock = in->clock;
	out->hdisplay = in->hdisplay;
	out->hsync_start = in->hsync_start;
	out->hsync_end = in->hsync_end;
	out->htotal = in->htotal;
	out->hskew = in->hskew;
	out->vdisplay = in->vdisplay;
	out->vsync_start = in->vsync_start;
	out->vsync_end = in->vsync_end;
	out->vtotal = in->vtotal;
	out->vscan = in->vscan;
	out->vrefresh = in->vrefresh;
	out->flags = in->flags;
	/*
	 * Old xf86-video-vmware (possibly others too) used to
	 * leave 'type' unititialized. Just ignore any bits we
	 * don't like. It's a just hint after all, and more
	 * useful for the kernel->userspace direction anyway.
	 */
	out->type = in->type & DRM_MODE_TYPE_ALL;
	strncpy(out->name, in->name, DRM_DISPLAY_MODE_LEN);
	out->name[DRM_DISPLAY_MODE_LEN-1] = 0;

	/* Clearing picture aspect ratio bits from out flags,
	 * as the aspect-ratio information is not stored in
	 * flags for kernel-mode, but in picture_aspect_ratio.
	 */
	out->flags &= ~DRM_MODE_FLAG_PIC_AR_MASK;

	switch (in->flags & DRM_MODE_FLAG_PIC_AR_MASK) {
	case DRM_MODE_FLAG_PIC_AR_4_3:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3;
		break;
	case DRM_MODE_FLAG_PIC_AR_16_9:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9;
		break;
	case DRM_MODE_FLAG_PIC_AR_64_27:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27;
		break;
	case DRM_MODE_FLAG_PIC_AR_256_135:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135;
		break;
	case DRM_MODE_FLAG_PIC_AR_NONE:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_NONE;
		break;
	default:
		return -EINVAL;
	}

	out->status = drm_mode_validate_driver(dev, out);
	if (out->status != MODE_OK)
		return -EINVAL;

	drm_mode_set_crtcinfo(out, CRTC_INTERLACE_HALVE_V);

	return 0;
}