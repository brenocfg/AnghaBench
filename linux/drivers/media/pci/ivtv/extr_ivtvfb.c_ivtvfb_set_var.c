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
struct v4l2_rect {scalar_t__ left; scalar_t__ top; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct osd_info {int bits_per_pixel; int bytes_per_pixel; int /*<<< orphan*/  fbvar_cur; } ;
struct ivtv_osd_coords {int /*<<< orphan*/  lines; int /*<<< orphan*/  pixel_stride; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {int yuv_forced_update; int /*<<< orphan*/  osd_full_h; int /*<<< orphan*/  osd_full_w; } ;
struct ivtv {TYPE_2__ yuv_info; struct osd_info* osd_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int vmode; scalar_t__ nonstd; scalar_t__ upper_margin; scalar_t__ left_margin; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; TYPE_1__ green; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_OSD_SET_FLICKER_STATE ; 
 int /*<<< orphan*/  CX2341X_OSD_SET_PIXEL_FORMAT ; 
#define  FB_VMODE_INTERLACED 129 
 int FB_VMODE_MASK ; 
#define  FB_VMODE_NONINTERLACED 128 
 int /*<<< orphan*/  IVTVFB_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  IVTVFB_DEBUG_WARN (char*) ; 
 int IVTV_OSD_BPP_16_444 ; 
 int IVTV_OSD_BPP_16_555 ; 
 int IVTV_OSD_BPP_16_565 ; 
 int IVTV_OSD_BPP_32 ; 
 int IVTV_OSD_BPP_8 ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ivtvfb_get_osd_coords (struct ivtv*,struct ivtv_osd_coords*) ; 
 int /*<<< orphan*/  ivtvfb_set_display_window (struct ivtv*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  ivtvfb_set_osd_coords (struct ivtv*,struct ivtv_osd_coords*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fb_var_screeninfo*,int) ; 
 int read_reg (int) ; 
 int /*<<< orphan*/  write_reg (int,int) ; 

__attribute__((used)) static int ivtvfb_set_var(struct ivtv *itv, struct fb_var_screeninfo *var)
{
	struct osd_info *oi = itv->osd_info;
	struct ivtv_osd_coords ivtv_osd;
	struct v4l2_rect ivtv_window;
	int osd_mode = -1;

	IVTVFB_DEBUG_INFO("ivtvfb_set_var\n");

	/* Select color space */
	if (var->nonstd) /* YUV */
		write_reg(read_reg(0x02a00) | 0x0002000, 0x02a00);
	else /* RGB  */
		write_reg(read_reg(0x02a00) & ~0x0002000, 0x02a00);

	/* Set the color mode */
	switch (var->bits_per_pixel) {
		case 8:
			osd_mode = IVTV_OSD_BPP_8;
			break;
		case 32:
			osd_mode = IVTV_OSD_BPP_32;
			break;
		case 16:
			switch (var->green.length) {
			case 4:
				osd_mode = IVTV_OSD_BPP_16_444;
				break;
			case 5:
				osd_mode = IVTV_OSD_BPP_16_555;
				break;
			case 6:
				osd_mode = IVTV_OSD_BPP_16_565;
				break;
			default:
				IVTVFB_DEBUG_WARN("ivtvfb_set_var - Invalid bpp\n");
			}
			break;
		default:
			IVTVFB_DEBUG_WARN("ivtvfb_set_var - Invalid bpp\n");
	}

	/* Set video mode. Although rare, the display can become scrambled even
	   if we don't change mode. Always 'bounce' to osd_mode via mode 0 */
	if (osd_mode != -1) {
		ivtv_vapi(itv, CX2341X_OSD_SET_PIXEL_FORMAT, 1, 0);
		ivtv_vapi(itv, CX2341X_OSD_SET_PIXEL_FORMAT, 1, osd_mode);
	}

	oi->bits_per_pixel = var->bits_per_pixel;
	oi->bytes_per_pixel = var->bits_per_pixel / 8;

	/* Set the flicker filter */
	switch (var->vmode & FB_VMODE_MASK) {
		case FB_VMODE_NONINTERLACED: /* Filter on */
			ivtv_vapi(itv, CX2341X_OSD_SET_FLICKER_STATE, 1, 1);
			break;
		case FB_VMODE_INTERLACED: /* Filter off */
			ivtv_vapi(itv, CX2341X_OSD_SET_FLICKER_STATE, 1, 0);
			break;
		default:
			IVTVFB_DEBUG_WARN("ivtvfb_set_var - Invalid video mode\n");
	}

	/* Read the current osd info */
	ivtvfb_get_osd_coords(itv, &ivtv_osd);

	/* Now set the OSD to the size we want */
	ivtv_osd.pixel_stride = var->xres_virtual;
	ivtv_osd.lines = var->yres_virtual;
	ivtv_osd.x = 0;
	ivtv_osd.y = 0;
	ivtvfb_set_osd_coords(itv, &ivtv_osd);

	/* Can't seem to find the right API combo for this.
	   Use another function which does what we need through direct register access. */
	ivtv_window.width = var->xres;
	ivtv_window.height = var->yres;

	/* Minimum margin cannot be 0, as X won't allow such a mode */
	if (!var->upper_margin)
		var->upper_margin++;
	if (!var->left_margin)
		var->left_margin++;
	ivtv_window.top = var->upper_margin - 1;
	ivtv_window.left = var->left_margin - 1;

	ivtvfb_set_display_window(itv, &ivtv_window);

	/* Pass screen size back to yuv handler */
	itv->yuv_info.osd_full_w = ivtv_osd.pixel_stride;
	itv->yuv_info.osd_full_h = ivtv_osd.lines;

	/* Force update of yuv registers */
	itv->yuv_info.yuv_forced_update = 1;

	/* Keep a copy of these settings */
	memcpy(&oi->fbvar_cur, var, sizeof(oi->fbvar_cur));

	IVTVFB_DEBUG_INFO("Display size: %dx%d (virtual %dx%d) @ %dbpp\n",
		      var->xres, var->yres,
		      var->xres_virtual, var->yres_virtual,
		      var->bits_per_pixel);

	IVTVFB_DEBUG_INFO("Display position: %d, %d\n",
		      var->left_margin, var->upper_margin);

	IVTVFB_DEBUG_INFO("Display filter: %s\n",
			(var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED ? "on" : "off");
	IVTVFB_DEBUG_INFO("Color space: %s\n", var->nonstd ? "YUV" : "RGB");

	return 0;
}