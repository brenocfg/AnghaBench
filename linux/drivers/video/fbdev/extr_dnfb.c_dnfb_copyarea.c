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
typedef  int ushort ;
typedef  int uint ;
struct TYPE_2__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ screen_base; } ;
struct fb_copyarea {int dy; int sy; int sx; int dx; int width; short height; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_CONTROL_0 ; 
 int /*<<< orphan*/  AP_CONTROL_3A ; 
 int /*<<< orphan*/  AP_WRITE_ENABLE ; 
 int NORMAL_MODE ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
void dnfb_copyarea(struct fb_info *info, const struct fb_copyarea *area)
{

	int incr, y_delta, pre_read = 0, x_end, x_word_count;
	uint start_mask, end_mask, dest;
	ushort *src, dummy;
	short i, j;

	incr = (area->dy <= area->sy) ? 1 : -1;

	src = (ushort *)(info->screen_base + area->sy * info->fix.line_length +
			(area->sx >> 4));
	dest = area->dy * (info->fix.line_length >> 1) + (area->dx >> 4);

	if (incr > 0) {
		y_delta = (info->fix.line_length * 8) - area->sx - area->width;
		x_end = area->dx + area->width - 1;
		x_word_count = (x_end >> 4) - (area->dx >> 4) + 1;
		start_mask = 0xffff0000 >> (area->dx & 0xf);
		end_mask = 0x7ffff >> (x_end & 0xf);
		out_8(AP_CONTROL_0,
		     (((area->dx & 0xf) - (area->sx & 0xf)) % 16) | (0x4 << 5));
		if ((area->dx & 0xf) < (area->sx & 0xf))
			pre_read = 1;
	} else {
		y_delta = -((info->fix.line_length * 8) - area->sx - area->width);
		x_end = area->dx - area->width + 1;
		x_word_count = (area->dx >> 4) - (x_end >> 4) + 1;
		start_mask = 0x7ffff >> (area->dx & 0xf);
		end_mask = 0xffff0000 >> (x_end & 0xf);
		out_8(AP_CONTROL_0,
		     ((-((area->sx & 0xf) - (area->dx & 0xf))) % 16) |
		     (0x4 << 5));
		if ((area->dx & 0xf) > (area->sx & 0xf))
			pre_read = 1;
	}

	for (i = 0; i < area->height; i++) {

		out_8(AP_CONTROL_3A, 0xc | (dest >> 16));

		if (pre_read) {
			dummy = *src;
			src += incr;
		}

		if (x_word_count) {
			out_8(AP_WRITE_ENABLE, start_mask);
			*src = dest;
			src += incr;
			dest += incr;
			out_8(AP_WRITE_ENABLE, 0);

			for (j = 1; j < (x_word_count - 1); j++) {
				*src = dest;
				src += incr;
				dest += incr;
			}

			out_8(AP_WRITE_ENABLE, start_mask);
			*src = dest;
			dest += incr;
			src += incr;
		} else {
			out_8(AP_WRITE_ENABLE, start_mask | end_mask);
			*src = dest;
			dest += incr;
			src += incr;
		}
		src += (y_delta / 16);
		dest += (y_delta / 16);
	}
	out_8(AP_CONTROL_0, NORMAL_MODE);
}