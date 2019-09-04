#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {size_t mode_ptr; } ;
struct nvbios {int* data; TYPE_1__ fp; } ;
struct nouveau_drm {struct nvbios vbios; } ;
struct drm_display_mode {int clock; int hdisplay; int hsync_start; int hsync_end; int htotal; int vdisplay; int vsync_start; int vsync_end; int vtotal; int type; int /*<<< orphan*/  status; int /*<<< orphan*/  flags; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_FLAG_NHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PVSYNC ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  MODE_OK ; 
 int ROM16 (int) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 int /*<<< orphan*/  memset (struct drm_display_mode*,int /*<<< orphan*/ ,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

bool nouveau_bios_fp_mode(struct drm_device *dev, struct drm_display_mode *mode)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvbios *bios = &drm->vbios;
	uint8_t *mode_entry = &bios->data[bios->fp.mode_ptr];

	if (!mode)	/* just checking whether we can produce a mode */
		return bios->fp.mode_ptr;

	memset(mode, 0, sizeof(struct drm_display_mode));
	/*
	 * For version 1.0 (version in byte 0):
	 * bytes 1-2 are "panel type", including bits on whether Colour/mono,
	 * single/dual link, and type (TFT etc.)
	 * bytes 3-6 are bits per colour in RGBX
	 */
	mode->clock = ROM16(mode_entry[7]) * 10;
	/* bytes 9-10 is HActive */
	mode->hdisplay = ROM16(mode_entry[11]) + 1;
	/*
	 * bytes 13-14 is HValid Start
	 * bytes 15-16 is HValid End
	 */
	mode->hsync_start = ROM16(mode_entry[17]) + 1;
	mode->hsync_end = ROM16(mode_entry[19]) + 1;
	mode->htotal = ROM16(mode_entry[21]) + 1;
	/* bytes 23-24, 27-30 similarly, but vertical */
	mode->vdisplay = ROM16(mode_entry[25]) + 1;
	mode->vsync_start = ROM16(mode_entry[31]) + 1;
	mode->vsync_end = ROM16(mode_entry[33]) + 1;
	mode->vtotal = ROM16(mode_entry[35]) + 1;
	mode->flags |= (mode_entry[37] & 0x10) ?
			DRM_MODE_FLAG_PHSYNC : DRM_MODE_FLAG_NHSYNC;
	mode->flags |= (mode_entry[37] & 0x1) ?
			DRM_MODE_FLAG_PVSYNC : DRM_MODE_FLAG_NVSYNC;
	/*
	 * bytes 38-39 relate to spread spectrum settings
	 * bytes 40-43 are something to do with PWM
	 */

	mode->status = MODE_OK;
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_set_name(mode);
	return bios->fp.mode_ptr;
}