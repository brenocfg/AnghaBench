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
struct drm_display_mode {unsigned int clock; unsigned int hdisplay; unsigned int hsync_start; unsigned int hsync_end; unsigned int htotal; unsigned int vdisplay; unsigned int vsync_start; unsigned int vsync_end; unsigned int vtotal; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct drm_device {int dummy; } ;
struct displayid_detailed_timings_1 {int* pixel_clock; int* hactive; int* hblank; int* hsync; int* hsw; int* vactive; int* vblank; int* vsync; int* vsw; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_FLAG_NHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_DRIVER ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_mode_create (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_vrefresh (struct drm_display_mode*) ; 

__attribute__((used)) static struct drm_display_mode *drm_mode_displayid_detailed(struct drm_device *dev,
							    struct displayid_detailed_timings_1 *timings)
{
	struct drm_display_mode *mode;
	unsigned pixel_clock = (timings->pixel_clock[0] |
				(timings->pixel_clock[1] << 8) |
				(timings->pixel_clock[2] << 16));
	unsigned hactive = (timings->hactive[0] | timings->hactive[1] << 8) + 1;
	unsigned hblank = (timings->hblank[0] | timings->hblank[1] << 8) + 1;
	unsigned hsync = (timings->hsync[0] | (timings->hsync[1] & 0x7f) << 8) + 1;
	unsigned hsync_width = (timings->hsw[0] | timings->hsw[1] << 8) + 1;
	unsigned vactive = (timings->vactive[0] | timings->vactive[1] << 8) + 1;
	unsigned vblank = (timings->vblank[0] | timings->vblank[1] << 8) + 1;
	unsigned vsync = (timings->vsync[0] | (timings->vsync[1] & 0x7f) << 8) + 1;
	unsigned vsync_width = (timings->vsw[0] | timings->vsw[1] << 8) + 1;
	bool hsync_positive = (timings->hsync[1] >> 7) & 0x1;
	bool vsync_positive = (timings->vsync[1] >> 7) & 0x1;
	mode = drm_mode_create(dev);
	if (!mode)
		return NULL;

	mode->clock = pixel_clock * 10;
	mode->hdisplay = hactive;
	mode->hsync_start = mode->hdisplay + hsync;
	mode->hsync_end = mode->hsync_start + hsync_width;
	mode->htotal = mode->hdisplay + hblank;

	mode->vdisplay = vactive;
	mode->vsync_start = mode->vdisplay + vsync;
	mode->vsync_end = mode->vsync_start + vsync_width;
	mode->vtotal = mode->vdisplay + vblank;

	mode->flags = 0;
	mode->flags |= hsync_positive ? DRM_MODE_FLAG_PHSYNC : DRM_MODE_FLAG_NHSYNC;
	mode->flags |= vsync_positive ? DRM_MODE_FLAG_PVSYNC : DRM_MODE_FLAG_NVSYNC;
	mode->type = DRM_MODE_TYPE_DRIVER;

	if (timings->flags & 0x80)
		mode->type |= DRM_MODE_TYPE_PREFERRED;
	mode->vrefresh = drm_mode_vrefresh(mode);
	drm_mode_set_name(mode);

	return mode;
}