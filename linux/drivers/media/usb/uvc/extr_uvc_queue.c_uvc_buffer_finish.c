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
struct vb2_buffer {scalar_t__ state; int /*<<< orphan*/  vb2_queue; } ;
struct uvc_video_queue {int dummy; } ;
struct uvc_streaming {int dummy; } ;
struct uvc_buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ VB2_BUF_STATE_DONE ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct uvc_streaming* uvc_queue_to_stream (struct uvc_video_queue*) ; 
 struct uvc_buffer* uvc_vbuf_to_buffer (struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  uvc_video_clock_update (struct uvc_streaming*,struct vb2_v4l2_buffer*,struct uvc_buffer*) ; 
 struct uvc_video_queue* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvc_buffer_finish(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);
	struct uvc_streaming *stream = uvc_queue_to_stream(queue);
	struct uvc_buffer *buf = uvc_vbuf_to_buffer(vbuf);

	if (vb->state == VB2_BUF_STATE_DONE)
		uvc_video_clock_update(stream, vbuf, buf);
}