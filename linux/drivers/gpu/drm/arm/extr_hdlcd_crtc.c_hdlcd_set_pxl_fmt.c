#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int offset; int length; } ;
struct TYPE_11__ {int offset; int length; } ;
struct TYPE_10__ {int offset; int length; } ;
struct simplefb_format {int bits_per_pixel; TYPE_6__ blue; TYPE_5__ green; TYPE_4__ red; int /*<<< orphan*/  fourcc; } ;
struct hdlcd_drm_private {int dummy; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
struct drm_crtc {TYPE_2__* primary; } ;
struct TYPE_9__ {int /*<<< orphan*/  format; } ;
struct TYPE_8__ {TYPE_1__* state; } ;
struct TYPE_7__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct simplefb_format*) ; 
 int /*<<< orphan*/  HDLCD_REG_BLUE_SELECT ; 
 int /*<<< orphan*/  HDLCD_REG_GREEN_SELECT ; 
 int /*<<< orphan*/  HDLCD_REG_PIXEL_FORMAT ; 
 int /*<<< orphan*/  HDLCD_REG_RED_SELECT ; 
 scalar_t__ WARN_ON (int) ; 
 struct hdlcd_drm_private* crtc_to_hdlcd_priv (struct drm_crtc*) ; 
 int /*<<< orphan*/  hdlcd_write (struct hdlcd_drm_private*,int /*<<< orphan*/ ,int) ; 
 struct simplefb_format* supported_formats ; 

__attribute__((used)) static int hdlcd_set_pxl_fmt(struct drm_crtc *crtc)
{
	unsigned int btpp;
	struct hdlcd_drm_private *hdlcd = crtc_to_hdlcd_priv(crtc);
	const struct drm_framebuffer *fb = crtc->primary->state->fb;
	uint32_t pixel_format;
	struct simplefb_format *format = NULL;
	int i;

	pixel_format = fb->format->format;

	for (i = 0; i < ARRAY_SIZE(supported_formats); i++) {
		if (supported_formats[i].fourcc == pixel_format)
			format = &supported_formats[i];
	}

	if (WARN_ON(!format))
		return 0;

	/* HDLCD uses 'bytes per pixel', zero means 1 byte */
	btpp = (format->bits_per_pixel + 7) / 8;
	hdlcd_write(hdlcd, HDLCD_REG_PIXEL_FORMAT, (btpp - 1) << 3);

	/*
	 * The format of the HDLCD_REG_<color>_SELECT register is:
	 *   - bits[23:16] - default value for that color component
	 *   - bits[11:8]  - number of bits to extract for each color component
	 *   - bits[4:0]   - index of the lowest bit to extract
	 *
	 * The default color value is used when bits[11:8] are zero, when the
	 * pixel is outside the visible frame area or when there is a
	 * buffer underrun.
	 */
	hdlcd_write(hdlcd, HDLCD_REG_RED_SELECT, format->red.offset |
#ifdef CONFIG_DRM_HDLCD_SHOW_UNDERRUN
		    0x00ff0000 |	/* show underruns in red */
#endif
		    ((format->red.length & 0xf) << 8));
	hdlcd_write(hdlcd, HDLCD_REG_GREEN_SELECT, format->green.offset |
		    ((format->green.length & 0xf) << 8));
	hdlcd_write(hdlcd, HDLCD_REG_BLUE_SELECT, format->blue.offset |
		    ((format->blue.length & 0xf) << 8));

	return 0;
}