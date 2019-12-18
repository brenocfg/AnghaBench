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
struct v4l2_m2m_ctx {int dummy; } ;
struct amvdec_session {int /*<<< orphan*/  esparser_queue_work; int /*<<< orphan*/  streamon_cap; int /*<<< orphan*/  streamon_out; struct v4l2_m2m_ctx* m2m_ctx; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (struct v4l2_m2m_ctx*,struct vb2_v4l2_buffer*) ; 
 struct amvdec_session* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vdec_codec_needs_recycle (struct amvdec_session*) ; 
 int /*<<< orphan*/  vdec_queue_recycle (struct amvdec_session*,struct vb2_buffer*) ; 

__attribute__((used)) static void vdec_vb2_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct amvdec_session *sess = vb2_get_drv_priv(vb->vb2_queue);
	struct v4l2_m2m_ctx *m2m_ctx = sess->m2m_ctx;

	v4l2_m2m_buf_queue(m2m_ctx, vbuf);

	if (!sess->streamon_out || !sess->streamon_cap)
		return;

	if (vb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    vdec_codec_needs_recycle(sess))
		vdec_queue_recycle(sess, vb);

	schedule_work(&sess->esparser_queue_work);
}