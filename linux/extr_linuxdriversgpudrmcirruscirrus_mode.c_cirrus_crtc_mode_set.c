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
struct drm_framebuffer {int* pitches; TYPE_2__* format; } ;
struct drm_display_mode {int htotal; int hsync_end; int hsync_start; int hdisplay; int vtotal; int vdisplay; } ;
struct drm_device {struct cirrus_device* dev_private; } ;
struct drm_crtc {TYPE_1__* primary; struct drm_device* dev; } ;
struct cirrus_device {int dummy; } ;
struct TYPE_4__ {int* cpp; } ;
struct TYPE_3__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int CL_CRT1A ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_DATA ; 
 int /*<<< orphan*/  SEQ_INDEX ; 
 int VGA_CRTC_H_DISP ; 
 int VGA_CRTC_H_SYNC_END ; 
 int VGA_CRTC_H_SYNC_START ; 
 int VGA_CRTC_H_TOTAL ; 
 int VGA_CRTC_MAX_SCAN ; 
 int VGA_CRTC_MODE ; 
 int VGA_CRTC_OFFSET ; 
 int VGA_CRTC_OVERFLOW ; 
 int VGA_CRTC_V_DISP_END ; 
 int VGA_CRTC_V_SYNC_END ; 
 int VGA_CRTC_V_TOTAL ; 
 int /*<<< orphan*/  VGA_GFX_MISC ; 
 int /*<<< orphan*/  VGA_GFX_MODE ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG_CRT (int,int) ; 
 int /*<<< orphan*/  WREG_GFX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG_HDR (int) ; 
 int /*<<< orphan*/  WREG_SEQ (int,int) ; 
 int /*<<< orphan*/  cirrus_crtc_do_set_base (struct drm_crtc*,struct drm_framebuffer*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static int cirrus_crtc_mode_set(struct drm_crtc *crtc,
				struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode,
				int x, int y, struct drm_framebuffer *old_fb)
{
	struct drm_device *dev = crtc->dev;
	struct cirrus_device *cdev = dev->dev_private;
	const struct drm_framebuffer *fb = crtc->primary->fb;
	int hsyncstart, hsyncend, htotal, hdispend;
	int vtotal, vdispend;
	int tmp;
	int sr07 = 0, hdr = 0;

	htotal = mode->htotal / 8;
	hsyncend = mode->hsync_end / 8;
	hsyncstart = mode->hsync_start / 8;
	hdispend = mode->hdisplay / 8;

	vtotal = mode->vtotal;
	vdispend = mode->vdisplay;

	vdispend -= 1;
	vtotal -= 2;

	htotal -= 5;
	hdispend -= 1;
	hsyncstart += 1;
	hsyncend += 1;

	WREG_CRT(VGA_CRTC_V_SYNC_END, 0x20);
	WREG_CRT(VGA_CRTC_H_TOTAL, htotal);
	WREG_CRT(VGA_CRTC_H_DISP, hdispend);
	WREG_CRT(VGA_CRTC_H_SYNC_START, hsyncstart);
	WREG_CRT(VGA_CRTC_H_SYNC_END, hsyncend);
	WREG_CRT(VGA_CRTC_V_TOTAL, vtotal & 0xff);
	WREG_CRT(VGA_CRTC_V_DISP_END, vdispend & 0xff);

	tmp = 0x40;
	if ((vdispend + 1) & 512)
		tmp |= 0x20;
	WREG_CRT(VGA_CRTC_MAX_SCAN, tmp);

	/*
	 * Overflow bits for values that don't fit in the standard registers
	 */
	tmp = 16;
	if (vtotal & 256)
		tmp |= 1;
	if (vdispend & 256)
		tmp |= 2;
	if ((vdispend + 1) & 256)
		tmp |= 8;
	if (vtotal & 512)
		tmp |= 32;
	if (vdispend & 512)
		tmp |= 64;
	WREG_CRT(VGA_CRTC_OVERFLOW, tmp);

	tmp = 0;

	/* More overflow bits */

	if ((htotal + 5) & 64)
		tmp |= 16;
	if ((htotal + 5) & 128)
		tmp |= 32;
	if (vtotal & 256)
		tmp |= 64;
	if (vtotal & 512)
		tmp |= 128;

	WREG_CRT(CL_CRT1A, tmp);

	/* Disable Hercules/CGA compatibility */
	WREG_CRT(VGA_CRTC_MODE, 0x03);

	WREG8(SEQ_INDEX, 0x7);
	sr07 = RREG8(SEQ_DATA);
	sr07 &= 0xe0;
	hdr = 0;
	switch (fb->format->cpp[0] * 8) {
	case 8:
		sr07 |= 0x11;
		break;
	case 16:
		sr07 |= 0x17;
		hdr = 0xc1;
		break;
	case 24:
		sr07 |= 0x15;
		hdr = 0xc5;
		break;
	case 32:
		sr07 |= 0x19;
		hdr = 0xc5;
		break;
	default:
		return -1;
	}

	WREG_SEQ(0x7, sr07);

	/* Program the pitch */
	tmp = fb->pitches[0] / 8;
	WREG_CRT(VGA_CRTC_OFFSET, tmp);

	/* Enable extended blanking and pitch bits, and enable full memory */
	tmp = 0x22;
	tmp |= (fb->pitches[0] >> 7) & 0x10;
	tmp |= (fb->pitches[0] >> 6) & 0x40;
	WREG_CRT(0x1b, tmp);

	/* Enable high-colour modes */
	WREG_GFX(VGA_GFX_MODE, 0x40);

	/* And set graphics mode */
	WREG_GFX(VGA_GFX_MISC, 0x01);

	WREG_HDR(hdr);
	cirrus_crtc_do_set_base(crtc, old_fb, x, y, 0);

	/* Unblank (needed on S3 resume, vgabios doesn't do it then) */
	outb(0x20, 0x3c0);
	return 0;
}