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
typedef  int u8 ;
struct TYPE_3__ {int width; } ;
struct vivid_dev {int* bitmap_cap; int clipcount_cap; TYPE_2__* clips_cap; TYPE_1__ compose_cap; } ;
struct v4l2_rect {int top; int height; int left; int width; } ;
struct TYPE_4__ {struct v4l2_rect c; } ;

/* Variables and functions */

__attribute__((used)) static bool valid_pix(struct vivid_dev *dev, int win_y, int win_x, int fb_y, int fb_x)
{
	int i;

	if (dev->bitmap_cap) {
		/*
		 * Only if the corresponding bit in the bitmap is set can
		 * the video pixel be shown. Coordinates are relative to
		 * the overlay window set by VIDIOC_S_FMT.
		 */
		const u8 *p = dev->bitmap_cap;
		unsigned stride = (dev->compose_cap.width + 7) / 8;

		if (!(p[stride * win_y + win_x / 8] & (1 << (win_x & 7))))
			return false;
	}

	for (i = 0; i < dev->clipcount_cap; i++) {
		/*
		 * Only if the framebuffer coordinate is not in any of the
		 * clip rectangles will be video pixel be shown.
		 */
		struct v4l2_rect *r = &dev->clips_cap[i].c;

		if (fb_y >= r->top && fb_y < r->top + r->height &&
		    fb_x >= r->left && fb_x < r->left + r->width)
			return false;
	}
	return true;
}