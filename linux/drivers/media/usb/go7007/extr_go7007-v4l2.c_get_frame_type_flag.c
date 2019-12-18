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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; } ;
struct go7007_buffer {int /*<<< orphan*/  frame_offset; TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_BFRAME ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_KEYFRAME ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_PFRAME ; 
#define  V4L2_PIX_FMT_MJPEG 131 
#define  V4L2_PIX_FMT_MPEG1 130 
#define  V4L2_PIX_FMT_MPEG2 129 
#define  V4L2_PIX_FMT_MPEG4 128 
 int* vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_frame_type_flag(struct go7007_buffer *vb, int format)
{
	u8 *ptr = vb2_plane_vaddr(&vb->vb.vb2_buf, 0);

	switch (format) {
	case V4L2_PIX_FMT_MJPEG:
		return V4L2_BUF_FLAG_KEYFRAME;
	case V4L2_PIX_FMT_MPEG4:
		switch ((ptr[vb->frame_offset + 4] >> 6) & 0x3) {
		case 0:
			return V4L2_BUF_FLAG_KEYFRAME;
		case 1:
			return V4L2_BUF_FLAG_PFRAME;
		case 2:
			return V4L2_BUF_FLAG_BFRAME;
		default:
			return 0;
		}
	case V4L2_PIX_FMT_MPEG1:
	case V4L2_PIX_FMT_MPEG2:
		switch ((ptr[vb->frame_offset + 5] >> 3) & 0x7) {
		case 1:
			return V4L2_BUF_FLAG_KEYFRAME;
		case 2:
			return V4L2_BUF_FLAG_PFRAME;
		case 3:
			return V4L2_BUF_FLAG_BFRAME;
		default:
			return 0;
		}
	}

	return 0;
}