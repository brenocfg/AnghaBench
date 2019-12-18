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
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_ctrl_vp8_frame_header {int flags; scalar_t__ alt_frame_ts; scalar_t__ golden_frame_ts; scalar_t__ last_frame_ts; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct hantro_ctx {TYPE_1__ fh; struct hantro_dev* dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_VP8_FRAME_HEADER_FLAG_SIGN_BIAS_ALT ; 
 int V4L2_VP8_FRAME_HEADER_FLAG_SIGN_BIAS_GOLDEN ; 
 int /*<<< orphan*/  VDPU_REG_VP8_ADDR_REF0 ; 
 int /*<<< orphan*/  VDPU_REG_VP8_ADDR_REF2_5 (int) ; 
 int /*<<< orphan*/  VDPU_REG_VP8_AREF_SIGN_BIAS ; 
 int /*<<< orphan*/  VDPU_REG_VP8_GREF_SIGN_BIAS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct vb2_v4l2_buffer* hantro_get_dst_buf (struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_get_ref (struct vb2_queue*,scalar_t__) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfg_ref(struct hantro_ctx *ctx,
		    const struct v4l2_ctrl_vp8_frame_header *hdr)
{
	struct hantro_dev *vpu = ctx->dev;
	struct vb2_v4l2_buffer *vb2_dst;
	struct vb2_queue *cap_q;
	dma_addr_t ref;

	cap_q = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	vb2_dst = hantro_get_dst_buf(ctx);

	ref = hantro_get_ref(cap_q, hdr->last_frame_ts);
	if (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	vdpu_write_relaxed(vpu, ref, VDPU_REG_VP8_ADDR_REF0);

	ref = hantro_get_ref(cap_q, hdr->golden_frame_ts);
	WARN_ON(!ref && hdr->golden_frame_ts);
	if (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	if (hdr->flags & V4L2_VP8_FRAME_HEADER_FLAG_SIGN_BIAS_GOLDEN)
		ref |= VDPU_REG_VP8_GREF_SIGN_BIAS;
	vdpu_write_relaxed(vpu, ref, VDPU_REG_VP8_ADDR_REF2_5(2));

	ref = hantro_get_ref(cap_q, hdr->alt_frame_ts);
	WARN_ON(!ref && hdr->alt_frame_ts);
	if (!ref)
		ref = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	if (hdr->flags & V4L2_VP8_FRAME_HEADER_FLAG_SIGN_BIAS_ALT)
		ref |= VDPU_REG_VP8_AREF_SIGN_BIAS;
	vdpu_write_relaxed(vpu, ref, VDPU_REG_VP8_ADDR_REF2_5(3));
}