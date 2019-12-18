#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct vbox_private {int /*<<< orphan*/  guest_pool; scalar_t__ single_framebuffer; } ;
struct vbox_crtc {int width; int height; int x; int x_hint; int y; int y_hint; scalar_t__ crtc_id; int fb_offset; scalar_t__ disconnected; } ;
struct drm_framebuffer {int* pitches; TYPE_4__* format; } ;
struct drm_crtc {int y; TYPE_5__* state; TYPE_3__* dev; TYPE_2__* primary; } ;
typedef  int s32 ;
struct TYPE_10__ {scalar_t__ enable; } ;
struct TYPE_9__ {int* cpp; } ;
struct TYPE_8__ {struct vbox_private* dev_private; } ;
struct TYPE_7__ {TYPE_1__* state; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int VBE_DISPI_ENABLED ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_BPP ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_ENABLE ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_VIRT_WIDTH ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_XRES ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_X_OFFSET ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_YRES ; 
 int /*<<< orphan*/  VBE_DISPI_INDEX_Y_OFFSET ; 
 int /*<<< orphan*/  VBVA_SCREEN_F_ACTIVE ; 
 int /*<<< orphan*/  VBVA_SCREEN_F_BLANK ; 
 int /*<<< orphan*/  VBVA_SCREEN_F_DISABLED ; 
 int /*<<< orphan*/  hgsmi_process_display_info (int /*<<< orphan*/ ,scalar_t__,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 struct vbox_crtc* to_vbox_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  vbox_write_ioport (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vbox_do_modeset(struct drm_crtc *crtc)
{
	struct drm_framebuffer *fb = crtc->primary->state->fb;
	struct vbox_crtc *vbox_crtc = to_vbox_crtc(crtc);
	struct vbox_private *vbox;
	int width, height, bpp, pitch;
	u16 flags;
	s32 x_offset, y_offset;

	vbox = crtc->dev->dev_private;
	width = vbox_crtc->width ? vbox_crtc->width : 640;
	height = vbox_crtc->height ? vbox_crtc->height : 480;
	bpp = fb ? fb->format->cpp[0] * 8 : 32;
	pitch = fb ? fb->pitches[0] : width * bpp / 8;
	x_offset = vbox->single_framebuffer ? vbox_crtc->x : vbox_crtc->x_hint;
	y_offset = vbox->single_framebuffer ? vbox_crtc->y : vbox_crtc->y_hint;

	/*
	 * This is the old way of setting graphics modes.  It assumed one screen
	 * and a frame-buffer at the start of video RAM.  On older versions of
	 * VirtualBox, certain parts of the code still assume that the first
	 * screen is programmed this way, so try to fake it.
	 */
	if (vbox_crtc->crtc_id == 0 && fb &&
	    vbox_crtc->fb_offset / pitch < 0xffff - crtc->y &&
	    vbox_crtc->fb_offset % (bpp / 8) == 0) {
		vbox_write_ioport(VBE_DISPI_INDEX_XRES, width);
		vbox_write_ioport(VBE_DISPI_INDEX_YRES, height);
		vbox_write_ioport(VBE_DISPI_INDEX_VIRT_WIDTH, pitch * 8 / bpp);
		vbox_write_ioport(VBE_DISPI_INDEX_BPP, bpp);
		vbox_write_ioport(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED);
		vbox_write_ioport(VBE_DISPI_INDEX_X_OFFSET,
			vbox_crtc->fb_offset % pitch / bpp * 8 + vbox_crtc->x);
		vbox_write_ioport(VBE_DISPI_INDEX_Y_OFFSET,
				  vbox_crtc->fb_offset / pitch + vbox_crtc->y);
	}

	flags = VBVA_SCREEN_F_ACTIVE;
	flags |= (fb && crtc->state->enable) ? 0 : VBVA_SCREEN_F_BLANK;
	flags |= vbox_crtc->disconnected ? VBVA_SCREEN_F_DISABLED : 0;
	hgsmi_process_display_info(vbox->guest_pool, vbox_crtc->crtc_id,
				   x_offset, y_offset,
				   vbox_crtc->x * bpp / 8 +
							vbox_crtc->y * pitch,
				   pitch, width, height, bpp, flags);
}