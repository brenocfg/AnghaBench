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
struct vb2_v4l2_buffer {int /*<<< orphan*/  flags; int /*<<< orphan*/  field; int /*<<< orphan*/  vb2_buf; } ;
struct vb2_buffer {int /*<<< orphan*/  timestamp; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct delta_frame {int /*<<< orphan*/  flags; int /*<<< orphan*/  field; int /*<<< orphan*/  dts; TYPE_1__ info; } ;

/* Variables and functions */
 struct delta_frame* to_frame (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delta_vb2_frame_finish(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct delta_frame *frame = to_frame(vbuf);

	/* update V4L2 fields for user */
	vb2_set_plane_payload(&vbuf->vb2_buf, 0, frame->info.size);
	vb->timestamp = frame->dts;
	vbuf->field = frame->field;
	vbuf->flags = frame->flags;
}