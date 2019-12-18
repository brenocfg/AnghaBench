#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {TYPE_3__* vb2_queue; } ;
struct TYPE_8__ {unsigned int width; unsigned int height; } ;
struct jpu_q_data {TYPE_4__ format; int /*<<< orphan*/  fmtinfo; } ;
struct TYPE_5__ {scalar_t__ m2m_ctx; } ;
struct jpu_ctx {TYPE_2__* jpu; TYPE_1__ fh; struct jpu_q_data out_q; int /*<<< orphan*/  encoder; } ;
struct jpu_buffer {scalar_t__ subsampling; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ JPU_JPEG_420 ; 
 scalar_t__ JPU_JPEG_422 ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  __jpu_try_fmt (struct jpu_ctx*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jpu_parse_hdr (void*,unsigned long,unsigned int*,unsigned int*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (scalar_t__,struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct jpu_ctx* vb2_get_drv_priv (TYPE_3__*) ; 
 unsigned long vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 void* vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct jpu_buffer* vb2_to_jpu_buffer (struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static void jpu_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct jpu_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	if (!ctx->encoder && V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		struct jpu_buffer *jpu_buf = vb2_to_jpu_buffer(vbuf);
		struct jpu_q_data *q_data, adjust;
		void *buffer = vb2_plane_vaddr(vb, 0);
		unsigned long buf_size = vb2_get_plane_payload(vb, 0);
		unsigned int width, height;

		u8 subsampling = jpu_parse_hdr(buffer, buf_size, &width,
						 &height);

		/* check if JPEG data basic parsing was successful */
		if (subsampling != JPU_JPEG_422 && subsampling != JPU_JPEG_420)
			goto format_error;

		q_data = &ctx->out_q;

		adjust = *q_data;
		adjust.format.width = width;
		adjust.format.height = height;

		__jpu_try_fmt(ctx, &adjust.fmtinfo, &adjust.format,
			      V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);

		if (adjust.format.width != q_data->format.width ||
		    adjust.format.height != q_data->format.height)
			goto format_error;

		/*
		 * keep subsampling in buffer to check it
		 * for compatibility in device_run
		 */
		jpu_buf->subsampling = subsampling;
	}

	if (ctx->fh.m2m_ctx)
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);

	return;

format_error:
	dev_err(ctx->jpu->dev, "incompatible or corrupted JPEG data\n");
	vb2_buffer_done(vb, VB2_BUF_STATE_ERROR);
}