#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int h_sync_off; int h_sync_width; int v_sync_off_width; int sync_off_width_high; int dtd_flags; int v_sync_off_high; scalar_t__ reserved; scalar_t__ sdvo_flags; } ;
struct TYPE_3__ {int clock; int h_active; int h_blank; int h_high; int v_active; int v_blank; int v_high; } ;
struct psb_intel_sdvo_dtd {TYPE_2__ part2; TYPE_1__ part1; } ;
struct drm_display_mode {int crtc_hdisplay; int crtc_vdisplay; int crtc_hblank_end; int crtc_hblank_start; int crtc_hsync_end; int crtc_hsync_start; int crtc_vblank_end; int crtc_vblank_start; int crtc_vsync_end; int crtc_vsync_start; int clock; int flags; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 

__attribute__((used)) static void psb_intel_sdvo_get_dtd_from_mode(struct psb_intel_sdvo_dtd *dtd,
					 const struct drm_display_mode *mode)
{
	uint16_t width, height;
	uint16_t h_blank_len, h_sync_len, v_blank_len, v_sync_len;
	uint16_t h_sync_offset, v_sync_offset;

	width = mode->crtc_hdisplay;
	height = mode->crtc_vdisplay;

	/* do some mode translations */
	h_blank_len = mode->crtc_hblank_end - mode->crtc_hblank_start;
	h_sync_len = mode->crtc_hsync_end - mode->crtc_hsync_start;

	v_blank_len = mode->crtc_vblank_end - mode->crtc_vblank_start;
	v_sync_len = mode->crtc_vsync_end - mode->crtc_vsync_start;

	h_sync_offset = mode->crtc_hsync_start - mode->crtc_hblank_start;
	v_sync_offset = mode->crtc_vsync_start - mode->crtc_vblank_start;

	dtd->part1.clock = mode->clock / 10;
	dtd->part1.h_active = width & 0xff;
	dtd->part1.h_blank = h_blank_len & 0xff;
	dtd->part1.h_high = (((width >> 8) & 0xf) << 4) |
		((h_blank_len >> 8) & 0xf);
	dtd->part1.v_active = height & 0xff;
	dtd->part1.v_blank = v_blank_len & 0xff;
	dtd->part1.v_high = (((height >> 8) & 0xf) << 4) |
		((v_blank_len >> 8) & 0xf);

	dtd->part2.h_sync_off = h_sync_offset & 0xff;
	dtd->part2.h_sync_width = h_sync_len & 0xff;
	dtd->part2.v_sync_off_width = (v_sync_offset & 0xf) << 4 |
		(v_sync_len & 0xf);
	dtd->part2.sync_off_width_high = ((h_sync_offset & 0x300) >> 2) |
		((h_sync_len & 0x300) >> 4) | ((v_sync_offset & 0x30) >> 2) |
		((v_sync_len & 0x30) >> 4);

	dtd->part2.dtd_flags = 0x18;
	if (mode->flags & DRM_MODE_FLAG_PHSYNC)
		dtd->part2.dtd_flags |= 0x2;
	if (mode->flags & DRM_MODE_FLAG_PVSYNC)
		dtd->part2.dtd_flags |= 0x4;

	dtd->part2.sdvo_flags = 0;
	dtd->part2.v_sync_off_high = v_sync_offset & 0xc0;
	dtd->part2.reserved = 0;
}