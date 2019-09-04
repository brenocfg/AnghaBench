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
struct TYPE_8__ {int left; unsigned int top; unsigned int height; int /*<<< orphan*/  width; } ;
struct sh_veu_vfmt {int offset_y; int /*<<< orphan*/  offset_c; TYPE_4__ frame; TYPE_3__* fmt; } ;
struct TYPE_6__ {int bytesperline; TYPE_1__* fmt; } ;
struct sh_veu_dev {TYPE_2__ vfmt_out; } ;
typedef  int dma_addr_t ;
struct TYPE_7__ {int fourcc; } ;
struct TYPE_5__ {int depth; } ;

/* Variables and functions */
 unsigned int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG () ; 
#define  V4L2_PIX_FMT_BGR666 135 
#define  V4L2_PIX_FMT_NV12 134 
#define  V4L2_PIX_FMT_NV16 133 
#define  V4L2_PIX_FMT_NV24 132 
#define  V4L2_PIX_FMT_RGB24 131 
#define  V4L2_PIX_FMT_RGB332 130 
#define  V4L2_PIX_FMT_RGB444 129 
#define  V4L2_PIX_FMT_RGB565 128 

__attribute__((used)) static void sh_veu_colour_offset(struct sh_veu_dev *veu, struct sh_veu_vfmt *vfmt)
{
	/* dst_left and dst_top validity will be verified in CROP / COMPOSE */
	unsigned int left = vfmt->frame.left & ~0x03;
	unsigned int top = vfmt->frame.top;
	dma_addr_t offset = (dma_addr_t)top * veu->vfmt_out.bytesperline +
			(((dma_addr_t)left * veu->vfmt_out.fmt->depth) >> 3);
	unsigned int y_line;

	vfmt->offset_y = offset;

	switch (vfmt->fmt->fourcc) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV24:
		y_line = ALIGN(vfmt->frame.width, 16);
		vfmt->offset_c = offset + y_line * vfmt->frame.height;
		break;
	case V4L2_PIX_FMT_RGB332:
	case V4L2_PIX_FMT_RGB444:
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_BGR666:
	case V4L2_PIX_FMT_RGB24:
		vfmt->offset_c = 0;
		break;
	default:
		BUG();
	}
}