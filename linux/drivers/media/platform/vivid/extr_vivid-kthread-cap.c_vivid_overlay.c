#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int width; int bytesperline; int height; } ;
struct TYPE_8__ {TYPE_3__ fmt; } ;
struct TYPE_6__ {unsigned int width; unsigned int height; unsigned int left; unsigned int top; } ;
struct tpg_data {unsigned int* bytesperline; } ;
struct vivid_dev {scalar_t__ clipcount_cap; scalar_t__ overlay_cap_field; int overlay_cap_left; int overlay_cap_top; TYPE_4__ fb_cap; TYPE_2__ compose_cap; int /*<<< orphan*/ * bitmap_cap; void* fb_vbase_cap; struct tpg_data tpg; } ;
struct TYPE_5__ {scalar_t__ field; int /*<<< orphan*/  vb2_buf; } ;
struct vivid_buffer {TYPE_1__ vb; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_TOP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int tpg_g_twopixelsize (struct tpg_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_pix (struct vivid_dev*,int,int,int,int) ; 
 void* vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vivid_overlay(struct vivid_dev *dev, struct vivid_buffer *buf)
{
	struct tpg_data *tpg = &dev->tpg;
	unsigned pixsize = tpg_g_twopixelsize(tpg, 0) / 2;
	void *vbase = dev->fb_vbase_cap;
	void *vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	unsigned img_width = dev->compose_cap.width;
	unsigned img_height = dev->compose_cap.height;
	unsigned stride = tpg->bytesperline[0];
	/* if quick is true, then valid_pix() doesn't have to be called */
	bool quick = dev->bitmap_cap == NULL && dev->clipcount_cap == 0;
	int x, y, w, out_x = 0;

	/*
	 * Overlay support is only supported for formats that have a twopixelsize
	 * that's >= 2. Warn and bail out if that's not the case.
	 */
	if (WARN_ON(pixsize == 0))
		return;
	if ((dev->overlay_cap_field == V4L2_FIELD_TOP ||
	     dev->overlay_cap_field == V4L2_FIELD_BOTTOM) &&
	    dev->overlay_cap_field != buf->vb.field)
		return;

	vbuf += dev->compose_cap.left * pixsize + dev->compose_cap.top * stride;
	x = dev->overlay_cap_left;
	w = img_width;
	if (x < 0) {
		out_x = -x;
		w = w - out_x;
		x = 0;
	} else {
		w = dev->fb_cap.fmt.width - x;
		if (w > img_width)
			w = img_width;
	}
	if (w <= 0)
		return;
	if (dev->overlay_cap_top >= 0)
		vbase += dev->overlay_cap_top * dev->fb_cap.fmt.bytesperline;
	for (y = dev->overlay_cap_top;
	     y < dev->overlay_cap_top + (int)img_height;
	     y++, vbuf += stride) {
		int px;

		if (y < 0 || y > dev->fb_cap.fmt.height)
			continue;
		if (quick) {
			memcpy(vbase + x * pixsize,
			       vbuf + out_x * pixsize, w * pixsize);
			vbase += dev->fb_cap.fmt.bytesperline;
			continue;
		}
		for (px = 0; px < w; px++) {
			if (!valid_pix(dev, y - dev->overlay_cap_top,
				       px + out_x, y, px + x))
				continue;
			memcpy(vbase + (px + x) * pixsize,
			       vbuf + (px + out_x) * pixsize,
			       pixsize);
		}
		vbase += dev->fb_cap.fmt.bytesperline;
	}
}