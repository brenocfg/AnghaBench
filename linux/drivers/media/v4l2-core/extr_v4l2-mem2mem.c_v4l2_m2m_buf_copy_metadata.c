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
typedef  int u32 ;
struct TYPE_2__ {int copied_timestamp; int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; TYPE_1__ vb2_buf; int /*<<< orphan*/  field; int /*<<< orphan*/  timecode; } ;

/* Variables and functions */
 int V4L2_BUF_FLAG_BFRAME ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int V4L2_BUF_FLAG_PFRAME ; 
 int V4L2_BUF_FLAG_TIMECODE ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 

void v4l2_m2m_buf_copy_metadata(const struct vb2_v4l2_buffer *out_vb,
				struct vb2_v4l2_buffer *cap_vb,
				bool copy_frame_flags)
{
	u32 mask = V4L2_BUF_FLAG_TIMECODE | V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

	if (copy_frame_flags)
		mask |= V4L2_BUF_FLAG_KEYFRAME | V4L2_BUF_FLAG_PFRAME |
			V4L2_BUF_FLAG_BFRAME;

	cap_vb->vb2_buf.timestamp = out_vb->vb2_buf.timestamp;

	if (out_vb->flags & V4L2_BUF_FLAG_TIMECODE)
		cap_vb->timecode = out_vb->timecode;
	cap_vb->field = out_vb->field;
	cap_vb->flags &= ~mask;
	cap_vb->flags |= out_vb->flags & mask;
	cap_vb->vb2_buf.copied_timestamp = 1;
}