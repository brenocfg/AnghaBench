#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {scalar_t__ type; int /*<<< orphan*/  vb2_queue; } ;
struct uvc_video_queue {int flags; } ;
struct uvc_buffer {scalar_t__ bytesused; scalar_t__ length; int /*<<< orphan*/  mem; scalar_t__ error; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  UVC_BUF_STATE_QUEUED ; 
 int UVC_QUEUE_DISCONNECTED ; 
 int /*<<< orphan*/  UVC_TRACE_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 
 struct uvc_buffer* uvc_vbuf_to_buffer (struct vb2_v4l2_buffer*) ; 
 struct uvc_video_queue* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvc_buffer_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);
	struct uvc_buffer *buf = uvc_vbuf_to_buffer(vbuf);

	if (vb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0)) {
		uvc_trace(UVC_TRACE_CAPTURE, "[E] Bytes used out of bounds.\n");
		return -EINVAL;
	}

	if (unlikely(queue->flags & UVC_QUEUE_DISCONNECTED))
		return -ENODEV;

	buf->state = UVC_BUF_STATE_QUEUED;
	buf->error = 0;
	buf->mem = vb2_plane_vaddr(vb, 0);
	buf->length = vb2_plane_size(vb, 0);
	if (vb->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		buf->bytesused = 0;
	else
		buf->bytesused = vb2_get_plane_payload(vb, 0);

	return 0;
}