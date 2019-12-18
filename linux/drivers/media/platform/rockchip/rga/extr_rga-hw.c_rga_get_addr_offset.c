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
struct rga_frame {unsigned int stride; unsigned int width; unsigned int height; TYPE_1__* fmt; } ;
struct rga_addr_offset {unsigned int y_off; unsigned int u_off; unsigned int v_off; } ;
struct rga_corners_addr_offset {struct rga_addr_offset right_bottom; struct rga_addr_offset right_top; struct rga_addr_offset left_bottom; struct rga_addr_offset left_top; } ;
struct TYPE_2__ {unsigned int x_div; unsigned int y_div; unsigned int uv_factor; } ;

/* Variables and functions */

__attribute__((used)) static struct rga_corners_addr_offset
rga_get_addr_offset(struct rga_frame *frm, unsigned int x, unsigned int y,
		    unsigned int w, unsigned int h)
{
	struct rga_corners_addr_offset offsets;
	struct rga_addr_offset *lt, *lb, *rt, *rb;
	unsigned int x_div = 0,
		     y_div = 0, uv_stride = 0, pixel_width = 0, uv_factor = 0;

	lt = &offsets.left_top;
	lb = &offsets.left_bottom;
	rt = &offsets.right_top;
	rb = &offsets.right_bottom;

	x_div = frm->fmt->x_div;
	y_div = frm->fmt->y_div;
	uv_factor = frm->fmt->uv_factor;
	uv_stride = frm->stride / x_div;
	pixel_width = frm->stride / frm->width;

	lt->y_off = y * frm->stride + x * pixel_width;
	lt->u_off =
		frm->width * frm->height + (y / y_div) * uv_stride + x / x_div;
	lt->v_off = lt->u_off + frm->width * frm->height / uv_factor;

	lb->y_off = lt->y_off + (h - 1) * frm->stride;
	lb->u_off = lt->u_off + (h / y_div - 1) * uv_stride;
	lb->v_off = lt->v_off + (h / y_div - 1) * uv_stride;

	rt->y_off = lt->y_off + (w - 1) * pixel_width;
	rt->u_off = lt->u_off + w / x_div - 1;
	rt->v_off = lt->v_off + w / x_div - 1;

	rb->y_off = lb->y_off + (w - 1) * pixel_width;
	rb->u_off = lb->u_off + w / x_div - 1;
	rb->v_off = lb->v_off + w / x_div - 1;

	return offsets;
}