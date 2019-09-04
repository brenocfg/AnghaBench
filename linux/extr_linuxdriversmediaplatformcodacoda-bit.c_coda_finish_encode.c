#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {scalar_t__ sequence; int flags; int /*<<< orphan*/  timecode; int /*<<< orphan*/  field; TYPE_3__ vb2_buf; } ;
struct coda_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_5__ {scalar_t__ gop_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct coda_ctx {scalar_t__ gopcounter; TYPE_2__ params; TYPE_1__ fh; struct coda_dev* dev; scalar_t__* vpu_header_size; int /*<<< orphan*/  reg_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_CMD_ENC_PIC_BB_START ; 
 int /*<<< orphan*/  CODA_REG_BIT_WR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODA_RET_ENC_PIC_FLAG ; 
 int /*<<< orphan*/  CODA_RET_ENC_PIC_SLICE_NUM ; 
 int /*<<< orphan*/  CODA_RET_ENC_PIC_TYPE ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int V4L2_BUF_FLAG_PFRAME ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  coda_debug ; 
 int /*<<< orphan*/  coda_m2m_buf_done (struct coda_ctx*,struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ coda_read (struct coda_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_coda_enc_pic_done (struct coda_ctx*,struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void coda_finish_encode(struct coda_ctx *ctx)
{
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	struct coda_dev *dev = ctx->dev;
	u32 wr_ptr, start_ptr;

	src_buf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	trace_coda_enc_pic_done(ctx, dst_buf);

	/* Get results from the coda */
	start_ptr = coda_read(dev, CODA_CMD_ENC_PIC_BB_START);
	wr_ptr = coda_read(dev, CODA_REG_BIT_WR_PTR(ctx->reg_idx));

	/* Calculate bytesused field */
	if (dst_buf->sequence == 0 ||
	    src_buf->flags & V4L2_BUF_FLAG_KEYFRAME) {
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, wr_ptr - start_ptr +
					ctx->vpu_header_size[0] +
					ctx->vpu_header_size[1] +
					ctx->vpu_header_size[2]);
	} else {
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, wr_ptr - start_ptr);
	}

	v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev, "frame size = %u\n",
		 wr_ptr - start_ptr);

	coda_read(dev, CODA_RET_ENC_PIC_SLICE_NUM);
	coda_read(dev, CODA_RET_ENC_PIC_FLAG);

	if (coda_read(dev, CODA_RET_ENC_PIC_TYPE) == 0) {
		dst_buf->flags |= V4L2_BUF_FLAG_KEYFRAME;
		dst_buf->flags &= ~V4L2_BUF_FLAG_PFRAME;
	} else {
		dst_buf->flags |= V4L2_BUF_FLAG_PFRAME;
		dst_buf->flags &= ~V4L2_BUF_FLAG_KEYFRAME;
	}

	dst_buf->vb2_buf.timestamp = src_buf->vb2_buf.timestamp;
	dst_buf->field = src_buf->field;
	dst_buf->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_buf->flags |=
		src_buf->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_buf->timecode = src_buf->timecode;

	v4l2_m2m_buf_done(src_buf, VB2_BUF_STATE_DONE);

	dst_buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
	coda_m2m_buf_done(ctx, dst_buf, VB2_BUF_STATE_DONE);

	ctx->gopcounter--;
	if (ctx->gopcounter < 0)
		ctx->gopcounter = ctx->params.gop_size - 1;

	v4l2_dbg(1, coda_debug, &dev->v4l2_dev,
		"job finished: encoding frame (%d) (%s)\n",
		dst_buf->sequence,
		(dst_buf->flags & V4L2_BUF_FLAG_KEYFRAME) ?
		"KEYFRAME" : "PFRAME");
}