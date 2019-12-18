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
struct TYPE_4__ {int height; scalar_t__ top; int width; scalar_t__ left; } ;
struct v4l2_window {TYPE_2__ w; } ;
struct v4l2_rect {scalar_t__ left; scalar_t__ width; scalar_t__ top; int height; } ;
struct v4l2_pix_format {scalar_t__ width; int height; } ;
struct TYPE_3__ {scalar_t__ height; scalar_t__ width; } ;
struct v4l2_framebuffer {TYPE_1__ fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ omap_vout_dss_omap24xx () ; 
 scalar_t__ omap_vout_dss_omap34xx () ; 

int omap_vout_new_crop(struct v4l2_pix_format *pix,
	      struct v4l2_rect *crop, struct v4l2_window *win,
	      struct v4l2_framebuffer *fbuf, const struct v4l2_rect *new_crop)
{
	struct v4l2_rect try_crop;
	unsigned long vresize, hresize;

	/* make a working copy of the new_crop rectangle */
	try_crop = *new_crop;

	/* adjust the cropping rectangle so it fits in the image */
	if (try_crop.left < 0) {
		try_crop.width += try_crop.left;
		try_crop.left = 0;
	}
	if (try_crop.top < 0) {
		try_crop.height += try_crop.top;
		try_crop.top = 0;
	}
	try_crop.width = (try_crop.width < pix->width) ?
		try_crop.width : pix->width;
	try_crop.height = (try_crop.height < pix->height) ?
		try_crop.height : pix->height;
	if (try_crop.left + try_crop.width > pix->width)
		try_crop.width = pix->width - try_crop.left;
	if (try_crop.top + try_crop.height > pix->height)
		try_crop.height = pix->height - try_crop.top;

	try_crop.width &= ~1;
	try_crop.height &= ~1;

	if (try_crop.width <= 0 || try_crop.height <= 0)
		return -EINVAL;

	if (omap_vout_dss_omap24xx()) {
		if (try_crop.height != win->w.height) {
			/* If we're resizing vertically, we can't support a
			 * crop width wider than 768 pixels.
			 */
			if (try_crop.width > 768)
				try_crop.width = 768;
		}
	}
	/* vertical resizing */
	vresize = (1024 * try_crop.height) / win->w.height;
	if (omap_vout_dss_omap24xx() && (vresize > 2048))
		vresize = 2048;
	else if (omap_vout_dss_omap34xx() && (vresize > 4096))
		vresize = 4096;

	win->w.height = ((1024 * try_crop.height) / vresize) & ~1;
	if (win->w.height == 0)
		win->w.height = 2;
	if (win->w.height + win->w.top > fbuf->fmt.height) {
		/* We made the preview window extend below the bottom of the
		 * display, so clip it to the display boundary and resize the
		 * cropping height to maintain the vertical resizing ratio.
		 */
		win->w.height = (fbuf->fmt.height - win->w.top) & ~1;
		if (try_crop.height == 0)
			try_crop.height = 2;
	}
	/* horizontal resizing */
	hresize = (1024 * try_crop.width) / win->w.width;
	if (omap_vout_dss_omap24xx() && (hresize > 2048))
		hresize = 2048;
	else if (omap_vout_dss_omap34xx() && (hresize > 4096))
		hresize = 4096;

	win->w.width = ((1024 * try_crop.width) / hresize) & ~1;
	if (win->w.width == 0)
		win->w.width = 2;
	if (win->w.width + win->w.left > fbuf->fmt.width) {
		/* We made the preview window extend past the right side of the
		 * display, so clip it to the display boundary and resize the
		 * cropping width to maintain the horizontal resizing ratio.
		 */
		win->w.width = (fbuf->fmt.width - win->w.left) & ~1;
		if (try_crop.width == 0)
			try_crop.width = 2;
	}
	if (omap_vout_dss_omap24xx()) {
		if ((try_crop.height/win->w.height) >= 2)
			try_crop.height = win->w.height * 2;

		if ((try_crop.width/win->w.width) >= 2)
			try_crop.width = win->w.width * 2;

		if (try_crop.width > 768) {
			/* The OMAP2420 vertical resizing line buffer is
			 * 768 pixels wide.  If the cropped image is wider
			 * than 768 pixels then it cannot be vertically resized.
			 */
			if (try_crop.height != win->w.height)
				try_crop.width = 768;
		}
	} else if (omap_vout_dss_omap34xx()) {
		if ((try_crop.height/win->w.height) >= 4)
			try_crop.height = win->w.height * 4;

		if ((try_crop.width/win->w.width) >= 4)
			try_crop.width = win->w.width * 4;
	}
	/* update our cropping rectangle and we're done */
	*crop = try_crop;
	return 0;
}