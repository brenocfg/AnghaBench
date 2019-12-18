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
struct uvc_video_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; } ;
struct uvc_buffer {TYPE_1__ buf; scalar_t__ bytesused; int /*<<< orphan*/  state; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  uvc_buffer_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvc_queue_buffer_requeue(struct uvc_video_queue *queue,
		struct uvc_buffer *buf)
{
	buf->error = 0;
	buf->state = UVC_BUF_STATE_QUEUED;
	buf->bytesused = 0;
	vb2_set_plane_payload(&buf->buf.vb2_buf, 0, 0);

	uvc_buffer_queue(&buf->buf.vb2_buf);
}