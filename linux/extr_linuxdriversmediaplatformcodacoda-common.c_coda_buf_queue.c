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
struct vb2_v4l2_buffer {scalar_t__ sequence; } ;
struct vb2_queue {scalar_t__ type; } ;
struct vb2_buffer {struct vb2_queue* vb2_queue; } ;
struct coda_q_data {scalar_t__ fourcc; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  h264_profile_idc; } ;
struct TYPE_4__ {scalar_t__ size; } ;
struct coda_ctx {scalar_t__ inst_type; TYPE_3__ fh; int /*<<< orphan*/  qsequence; int /*<<< orphan*/  bitstream_mutex; TYPE_2__ params; TYPE_1__ bitstream; } ;

/* Variables and functions */
 scalar_t__ CODA_INST_ENCODER ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  coda_bit_stream_end_flag (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_fill_bitstream (struct coda_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coda_sps_parse_profile (struct coda_ctx*,struct vb2_buffer*) ; 
 int /*<<< orphan*/  coda_update_h264_level_ctrl (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_update_h264_profile_ctrl (struct coda_ctx*) ; 
 struct coda_q_data* get_q_data (struct coda_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (int /*<<< orphan*/ ,struct vb2_v4l2_buffer*) ; 
 struct coda_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 scalar_t__ vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (struct vb2_queue*) ; 

__attribute__((used)) static void coda_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct coda_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct vb2_queue *vq = vb->vb2_queue;
	struct coda_q_data *q_data;

	q_data = get_q_data(ctx, vb->vb2_queue->type);

	/*
	 * In the decoder case, immediately try to copy the buffer into the
	 * bitstream ringbuffer and mark it as ready to be dequeued.
	 */
	if (ctx->bitstream.size && vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		/*
		 * For backwards compatibility, queuing an empty buffer marks
		 * the stream end
		 */
		if (vb2_get_plane_payload(vb, 0) == 0)
			coda_bit_stream_end_flag(ctx);

		if (q_data->fourcc == V4L2_PIX_FMT_H264) {
			/*
			 * Unless already done, try to obtain profile_idc and
			 * level_idc from the SPS header. This allows to decide
			 * whether to enable reordering during sequence
			 * initialization.
			 */
			if (!ctx->params.h264_profile_idc) {
				coda_sps_parse_profile(ctx, vb);
				coda_update_h264_profile_ctrl(ctx);
				coda_update_h264_level_ctrl(ctx);
			}
		}

		mutex_lock(&ctx->bitstream_mutex);
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
		if (vb2_is_streaming(vb->vb2_queue))
			/* This set buf->sequence = ctx->qsequence++ */
			coda_fill_bitstream(ctx, NULL);
		mutex_unlock(&ctx->bitstream_mutex);
	} else {
		if (ctx->inst_type == CODA_INST_ENCODER &&
		    vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			vbuf->sequence = ctx->qsequence++;
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
	}
}