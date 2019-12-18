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
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_ctrl_vp8_frame_header {int flags; scalar_t__ alt_frame_ts; scalar_t__ golden_frame_ts; scalar_t__ last_frame_ts; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_6__ {TYPE_2__* m2m_ctx; } ;
struct hantro_ctx {struct hantro_dev* dev; TYPE_3__ fh; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {struct vb2_queue q; } ;
struct TYPE_5__ {TYPE_1__ cap_q_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  G1_REG_ADDR_REF (int) ; 
 int /*<<< orphan*/  G1_REG_ADDR_REF_TOPC_E ; 
 int V4L2_VP8_FRAME_HEADER_FLAG_SIGN_BIAS_ALT ; 
 int V4L2_VP8_FRAME_HEADER_FLAG_SIGN_BIAS_GOLDEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct vb2_v4l2_buffer* hantro_get_dst_buf (struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_get_ref (struct vb2_queue*,scalar_t__) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfg_ref(struct hantro_ctx *ctx,
		    const struct v4l2_ctrl_vp8_frame_header *hdr)
{
	struct vb2_queue *cap_q = &ctx->fh.m2m_ctx->cap_q_ctx.q;
	struct hantro_dev *vpu = ctx->dev;
	struct vb2_v4l2_buffer *vb2_dst;
	dma_addr_t ref;

	vb2_dst = hantro_get_dst_buf(ctx);

	ref = hantro_get_ref(cap_q, hdr->last_frame_ts);
	if (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	vdpu_write_relaxed(vpu, ref, G1_REG_ADDR_REF(0));

	ref = hantro_get_ref(cap_q, hdr->golden_frame_ts);
	WARN_ON(!ref && hdr->golden_frame_ts);
	if (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	if (hdr->flags & V4L2_VP8_FRAME_HEADER_FLAG_SIGN_BIAS_GOLDEN)
		ref |= G1_REG_ADDR_REF_TOPC_E;
	vdpu_write_relaxed(vpu, ref, G1_REG_ADDR_REF(4));

	ref = hantro_get_ref(cap_q, hdr->alt_frame_ts);
	WARN_ON(!ref && hdr->alt_frame_ts);
	if (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	if (hdr->flags & V4L2_VP8_FRAME_HEADER_FLAG_SIGN_BIAS_ALT)
		ref |= G1_REG_ADDR_REF_TOPC_E;
	vdpu_write_relaxed(vpu, ref, G1_REG_ADDR_REF(5));
}