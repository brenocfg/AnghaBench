#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {scalar_t__ type; } ;
struct TYPE_4__ {int numerator; int denominator; } ;
struct amvdec_session {int streamon_out; int streamon_cap; scalar_t__ status; int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/  vififo_paddr; int /*<<< orphan*/  vififo_vaddr; int /*<<< orphan*/  vififo_size; struct amvdec_core* core; int /*<<< orphan*/  recycle_thread; scalar_t__ sequence_cap; int /*<<< orphan*/  ctrl_min_buf_capture; int /*<<< orphan*/  esparser_queued_bufs; TYPE_2__ pixelaspect; scalar_t__ wrap_count; scalar_t__ last_offset; scalar_t__ keyframe_found; scalar_t__ should_stop; TYPE_1__* fmt_out; } ;
struct amvdec_core {int /*<<< orphan*/  dev; struct amvdec_session* cur_sess; } ;
struct amvdec_codec_ops {int /*<<< orphan*/  (* resume ) (struct amvdec_session*) ;} ;
struct TYPE_3__ {struct amvdec_codec_ops* codec_ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SIZE_VIFIFO ; 
 scalar_t__ STATUS_NEEDS_RESUME ; 
 void* STATUS_RUNNING ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct amvdec_session*,char*) ; 
 int /*<<< orphan*/  stub1 (struct amvdec_session*) ; 
 int /*<<< orphan*/  v4l2_ctrl_s_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 struct amvdec_session* vb2_get_drv_priv (struct vb2_queue*) ; 
 scalar_t__ vdec_codec_needs_recycle (struct amvdec_session*) ; 
 int vdec_poweron (struct amvdec_session*) ; 
 int /*<<< orphan*/  vdec_recycle_thread ; 

__attribute__((used)) static int vdec_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct amvdec_session *sess = vb2_get_drv_priv(q);
	struct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	struct amvdec_core *core = sess->core;
	struct vb2_v4l2_buffer *buf;
	int ret;

	if (core->cur_sess && core->cur_sess != sess) {
		ret = -EBUSY;
		goto bufs_done;
	}

	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		sess->streamon_out = 1;
	else
		sess->streamon_cap = 1;

	if (!sess->streamon_out || !sess->streamon_cap)
		return 0;

	if (sess->status == STATUS_NEEDS_RESUME &&
	    q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		codec_ops->resume(sess);
		sess->status = STATUS_RUNNING;
		return 0;
	}

	sess->vififo_size = SIZE_VIFIFO;
	sess->vififo_vaddr =
		dma_alloc_coherent(sess->core->dev, sess->vififo_size,
				   &sess->vififo_paddr, GFP_KERNEL);
	if (!sess->vififo_vaddr) {
		dev_err(sess->core->dev, "Failed to request VIFIFO buffer\n");
		ret = -ENOMEM;
		goto bufs_done;
	}

	sess->should_stop = 0;
	sess->keyframe_found = 0;
	sess->last_offset = 0;
	sess->wrap_count = 0;
	sess->pixelaspect.numerator = 1;
	sess->pixelaspect.denominator = 1;
	atomic_set(&sess->esparser_queued_bufs, 0);
	v4l2_ctrl_s_ctrl(sess->ctrl_min_buf_capture, 1);

	ret = vdec_poweron(sess);
	if (ret)
		goto vififo_free;

	sess->sequence_cap = 0;
	if (vdec_codec_needs_recycle(sess))
		sess->recycle_thread = kthread_run(vdec_recycle_thread, sess,
						   "vdec_recycle");

	sess->status = STATUS_RUNNING;
	core->cur_sess = sess;

	return 0;

vififo_free:
	dma_free_coherent(sess->core->dev, sess->vififo_size,
			  sess->vififo_vaddr, sess->vififo_paddr);
bufs_done:
	while ((buf = v4l2_m2m_src_buf_remove(sess->m2m_ctx)))
		v4l2_m2m_buf_done(buf, VB2_BUF_STATE_QUEUED);
	while ((buf = v4l2_m2m_dst_buf_remove(sess->m2m_ctx)))
		v4l2_m2m_buf_done(buf, VB2_BUF_STATE_QUEUED);

	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		sess->streamon_out = 0;
	else
		sess->streamon_cap = 0;

	return ret;
}