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
struct vb2_queue {scalar_t__ type; } ;
struct amvdec_session {scalar_t__ status; scalar_t__ streamon_cap; int /*<<< orphan*/  m2m_ctx; scalar_t__ streamon_out; int /*<<< orphan*/ * priv; int /*<<< orphan*/  vififo_paddr; int /*<<< orphan*/  vififo_vaddr; int /*<<< orphan*/  vififo_size; struct amvdec_core* core; int /*<<< orphan*/  recycle_thread; } ;
struct amvdec_core {int /*<<< orphan*/ * cur_sess; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ STATUS_NEEDS_RESUME ; 
 scalar_t__ STATUS_RUNNING ; 
 scalar_t__ STATUS_STOPPED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 struct amvdec_session* vb2_get_drv_priv (struct vb2_queue*) ; 
 scalar_t__ vdec_codec_needs_recycle (struct amvdec_session*) ; 
 int /*<<< orphan*/  vdec_free_canvas (struct amvdec_session*) ; 
 int /*<<< orphan*/  vdec_poweroff (struct amvdec_session*) ; 
 int /*<<< orphan*/  vdec_reset_bufs_recycle (struct amvdec_session*) ; 
 int /*<<< orphan*/  vdec_reset_timestamps (struct amvdec_session*) ; 

__attribute__((used)) static void vdec_stop_streaming(struct vb2_queue *q)
{
	struct amvdec_session *sess = vb2_get_drv_priv(q);
	struct amvdec_core *core = sess->core;
	struct vb2_v4l2_buffer *buf;

	if (sess->status == STATUS_RUNNING ||
	    (sess->status == STATUS_NEEDS_RESUME &&
	     (!sess->streamon_out || !sess->streamon_cap))) {
		if (vdec_codec_needs_recycle(sess))
			kthread_stop(sess->recycle_thread);

		vdec_poweroff(sess);
		vdec_free_canvas(sess);
		dma_free_coherent(sess->core->dev, sess->vififo_size,
				  sess->vififo_vaddr, sess->vififo_paddr);
		vdec_reset_timestamps(sess);
		vdec_reset_bufs_recycle(sess);
		kfree(sess->priv);
		sess->priv = NULL;
		core->cur_sess = NULL;
		sess->status = STATUS_STOPPED;
	}

	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		while ((buf = v4l2_m2m_src_buf_remove(sess->m2m_ctx)))
			v4l2_m2m_buf_done(buf, VB2_BUF_STATE_ERROR);

		sess->streamon_out = 0;
	} else {
		while ((buf = v4l2_m2m_dst_buf_remove(sess->m2m_ctx)))
			v4l2_m2m_buf_done(buf, VB2_BUF_STATE_ERROR);

		sess->streamon_cap = 0;
	}
}