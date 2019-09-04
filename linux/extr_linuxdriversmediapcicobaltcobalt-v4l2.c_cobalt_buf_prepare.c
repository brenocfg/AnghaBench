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
struct vb2_v4l2_buffer {int /*<<< orphan*/  field; } ;
struct vb2_buffer {TYPE_1__* vb2_queue; } ;
struct cobalt_stream {int stride; int height; } ;
struct TYPE_2__ {struct cobalt_stream* drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cobalt_buf_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct cobalt_stream *s = vb->vb2_queue->drv_priv;

	vb2_set_plane_payload(vb, 0, s->stride * s->height);
	vbuf->field = V4L2_FIELD_NONE;
	return 0;
}