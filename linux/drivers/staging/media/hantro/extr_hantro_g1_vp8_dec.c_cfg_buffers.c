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
typedef  int /*<<< orphan*/  u32 ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct v4l2_vp8_segment_header {int flags; } ;
struct v4l2_ctrl_vp8_frame_header {struct v4l2_vp8_segment_header segment_header; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct TYPE_6__ {TYPE_2__ segment_map; TYPE_1__ prob_tbl; } ;
struct hantro_ctx {TYPE_3__ vp8_dec; struct hantro_dev* dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  G1_REG_ADDR_DST ; 
 int /*<<< orphan*/  G1_REG_ADDR_QTABLE ; 
 int /*<<< orphan*/  G1_REG_FWD_PIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G1_REG_FWD_PIC1_SEGMENT_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G1_REG_FWD_PIC1_SEGMENT_E ; 
 int /*<<< orphan*/  G1_REG_FWD_PIC1_SEGMENT_UPD_E ; 
 int V4L2_VP8_SEGMENT_HEADER_FLAG_ENABLED ; 
 int V4L2_VP8_SEGMENT_HEADER_FLAG_UPDATE_MAP ; 
 struct vb2_v4l2_buffer* hantro_get_dst_buf (struct hantro_ctx*) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfg_buffers(struct hantro_ctx *ctx,
			const struct v4l2_ctrl_vp8_frame_header *hdr)
{
	const struct v4l2_vp8_segment_header *seg = &hdr->segment_header;
	struct hantro_dev *vpu = ctx->dev;
	struct vb2_v4l2_buffer *vb2_dst;
	dma_addr_t dst_dma;
	u32 reg;

	vb2_dst = hantro_get_dst_buf(ctx);

	/* Set probability table buffer address */
	vdpu_write_relaxed(vpu, ctx->vp8_dec.prob_tbl.dma,
			   G1_REG_ADDR_QTABLE);

	/* Set segment map address */
	reg = G1_REG_FWD_PIC1_SEGMENT_BASE(ctx->vp8_dec.segment_map.dma);
	if (seg->flags & V4L2_VP8_SEGMENT_HEADER_FLAG_ENABLED) {
		reg |= G1_REG_FWD_PIC1_SEGMENT_E;
		if (seg->flags & V4L2_VP8_SEGMENT_HEADER_FLAG_UPDATE_MAP)
			reg |= G1_REG_FWD_PIC1_SEGMENT_UPD_E;
	}
	vdpu_write_relaxed(vpu, reg, G1_REG_FWD_PIC(0));

	dst_dma = vb2_dma_contig_plane_dma_addr(&vb2_dst->vb2_buf, 0);
	vdpu_write_relaxed(vpu, dst_dma, G1_REG_ADDR_DST);
}