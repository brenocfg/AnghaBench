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
struct TYPE_4__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; int /*<<< orphan*/  timecode; TYPE_2__ vb2_buf; int /*<<< orphan*/  field; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct jpu_ctx {TYPE_1__ fh; scalar_t__ encoder; } ;
struct jpu {int /*<<< orphan*/  lock; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/ * curr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  JCCMD ; 
 unsigned int JCCMD_JEND ; 
 unsigned int JCCMD_SRST ; 
 int /*<<< orphan*/  JCDERR ; 
 int JCDERR_MASK ; 
 int /*<<< orphan*/  JCDTCD ; 
 int /*<<< orphan*/  JCDTCM ; 
 int /*<<< orphan*/  JCDTCU ; 
 int /*<<< orphan*/  JINTS ; 
 unsigned int JINTS_ERR ; 
 unsigned int JINTS_MASK ; 
 unsigned int JINTS_PROCESS_COMPL ; 
 unsigned int JINTS_TRANSF_COMPL ; 
 scalar_t__ JPU_JPEG_HDR_SIZE ; 
 int V4L2_BUF_FLAG_BFRAME ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int V4L2_BUF_FLAG_PFRAME ; 
 int V4L2_BUF_FLAG_TIMECODE ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * error_to_text ; 
 int jpu_read (struct jpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpu_write (struct jpu*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct jpu_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t jpu_irq_handler(int irq, void *dev_id)
{
	struct jpu *jpu = dev_id;
	struct jpu_ctx *curr_ctx;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	unsigned int int_status;

	int_status = jpu_read(jpu, JINTS);

	/* ...spurious interrupt */
	if (!((JINTS_TRANSF_COMPL | JINTS_PROCESS_COMPL | JINTS_ERR) &
	    int_status))
		return IRQ_NONE;

	/* ...clear interrupts */
	jpu_write(jpu, ~(int_status & JINTS_MASK), JINTS);
	if (int_status & (JINTS_ERR | JINTS_PROCESS_COMPL))
		jpu_write(jpu, JCCMD_JEND, JCCMD);

	spin_lock(&jpu->lock);

	if ((int_status & JINTS_PROCESS_COMPL) &&
	   !(int_status & JINTS_TRANSF_COMPL))
		goto handled;

	curr_ctx = v4l2_m2m_get_curr_priv(jpu->m2m_dev);
	if (!curr_ctx) {
		/* ...instance is not running */
		dev_err(jpu->dev, "no active context for m2m\n");
		goto handled;
	}

	src_buf = v4l2_m2m_src_buf_remove(curr_ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_remove(curr_ctx->fh.m2m_ctx);

	if (int_status & JINTS_TRANSF_COMPL) {
		if (curr_ctx->encoder) {
			unsigned long payload_size = jpu_read(jpu, JCDTCU) << 16
						   | jpu_read(jpu, JCDTCM) << 8
						   | jpu_read(jpu, JCDTCD);
			vb2_set_plane_payload(&dst_buf->vb2_buf, 0,
				payload_size + JPU_JPEG_HDR_SIZE);
		}

		dst_buf->field = src_buf->field;
		dst_buf->vb2_buf.timestamp = src_buf->vb2_buf.timestamp;
		if (src_buf->flags & V4L2_BUF_FLAG_TIMECODE)
			dst_buf->timecode = src_buf->timecode;
		dst_buf->flags = src_buf->flags &
			(V4L2_BUF_FLAG_TIMECODE | V4L2_BUF_FLAG_KEYFRAME |
			 V4L2_BUF_FLAG_PFRAME | V4L2_BUF_FLAG_BFRAME |
			 V4L2_BUF_FLAG_TSTAMP_SRC_MASK);

		v4l2_m2m_buf_done(src_buf, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_done(dst_buf, VB2_BUF_STATE_DONE);
	} else if (int_status & JINTS_ERR) {
		unsigned char error = jpu_read(jpu, JCDERR) & JCDERR_MASK;

		dev_dbg(jpu->dev, "processing error: %#X: %s\n", error,
			error_to_text[error]);

		v4l2_m2m_buf_done(src_buf, VB2_BUF_STATE_ERROR);
		v4l2_m2m_buf_done(dst_buf, VB2_BUF_STATE_ERROR);
	}

	jpu->curr = NULL;

	/* ...reset JPU after completion */
	jpu_write(jpu, JCCMD_SRST, JCCMD);
	spin_unlock(&jpu->lock);

	v4l2_m2m_job_finish(jpu->m2m_dev, curr_ctx->fh.m2m_ctx);

	return IRQ_HANDLED;

handled:
	spin_unlock(&jpu->lock);
	return IRQ_HANDLED;
}