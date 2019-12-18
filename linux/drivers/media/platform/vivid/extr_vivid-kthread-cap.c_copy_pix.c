#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int width; scalar_t__ top; scalar_t__ left; } ;
struct vivid_dev {int overlay_out_left; int overlay_out_top; int* bitmap_out; int clipcount_out; int fbuf_out_flags; scalar_t__ const chromakey_out; TYPE_3__* fmt_cap; scalar_t__ global_alpha_out; TYPE_2__* clips_out; TYPE_1__ compose_out; } ;
struct v4l2_rect {int top; int height; int left; int width; } ;
struct TYPE_6__ {int alpha_mask; } ;
struct TYPE_5__ {struct v4l2_rect c; } ;

/* Variables and functions */
 int V4L2_FBUF_FLAG_CHROMAKEY ; 
 int V4L2_FBUF_FLAG_GLOBAL_ALPHA ; 
 int V4L2_FBUF_FLAG_LOCAL_ALPHA ; 
 int V4L2_FBUF_FLAG_LOCAL_INV_ALPHA ; 
 int V4L2_FBUF_FLAG_SRC_CHROMAKEY ; 

__attribute__((used)) static void copy_pix(struct vivid_dev *dev, int win_y, int win_x,
			u16 *cap, const u16 *osd)
{
	u16 out;
	int left = dev->overlay_out_left;
	int top = dev->overlay_out_top;
	int fb_x = win_x + left;
	int fb_y = win_y + top;
	int i;

	out = *cap;
	*cap = *osd;
	if (dev->bitmap_out) {
		const u8 *p = dev->bitmap_out;
		unsigned stride = (dev->compose_out.width + 7) / 8;

		win_x -= dev->compose_out.left;
		win_y -= dev->compose_out.top;
		if (!(p[stride * win_y + win_x / 8] & (1 << (win_x & 7))))
			return;
	}

	for (i = 0; i < dev->clipcount_out; i++) {
		struct v4l2_rect *r = &dev->clips_out[i].c;

		if (fb_y >= r->top && fb_y < r->top + r->height &&
		    fb_x >= r->left && fb_x < r->left + r->width)
			return;
	}
	if ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_CHROMAKEY) &&
	    *osd != dev->chromakey_out)
		return;
	if ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_SRC_CHROMAKEY) &&
	    out == dev->chromakey_out)
		return;
	if (dev->fmt_cap->alpha_mask) {
		if ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_GLOBAL_ALPHA) &&
		    dev->global_alpha_out)
			return;
		if ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_LOCAL_ALPHA) &&
		    *cap & dev->fmt_cap->alpha_mask)
			return;
		if ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_LOCAL_INV_ALPHA) &&
		    !(*cap & dev->fmt_cap->alpha_mask))
			return;
	}
	*cap = out;
}