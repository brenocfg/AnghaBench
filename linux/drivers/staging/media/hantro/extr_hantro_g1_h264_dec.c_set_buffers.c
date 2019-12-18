#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct hantro_h264_dec_ctrls {TYPE_2__* slices; TYPE_1__* sps; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_9__ {scalar_t__ dma; } ;
struct TYPE_10__ {size_t pic_size; TYPE_4__ priv; struct hantro_h264_dec_ctrls ctrls; } ;
struct TYPE_8__ {int /*<<< orphan*/  width; } ;
struct hantro_ctx {TYPE_5__ h264_dec; TYPE_3__ dst_fmt; struct hantro_dev* dev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int profile_idc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G1_REG_ADDR_DIR_MV ; 
 int /*<<< orphan*/  G1_REG_ADDR_DST ; 
 int /*<<< orphan*/  G1_REG_ADDR_QTABLE ; 
 int /*<<< orphan*/  G1_REG_ADDR_STR ; 
 int H264_MB_WIDTH (int /*<<< orphan*/ ) ; 
 int V4L2_H264_SLICE_FLAG_BOTTOM_FIELD ; 
 struct vb2_v4l2_buffer* hantro_get_dst_buf (struct hantro_ctx*) ; 
 struct vb2_v4l2_buffer* hantro_get_src_buf (struct hantro_ctx*) ; 
 size_t round_up (size_t,int) ; 
 scalar_t__ vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_buffers(struct hantro_ctx *ctx)
{
	const struct hantro_h264_dec_ctrls *ctrls = &ctx->h264_dec.ctrls;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	struct hantro_dev *vpu = ctx->dev;
	dma_addr_t src_dma, dst_dma;

	src_buf = hantro_get_src_buf(ctx);
	dst_buf = hantro_get_dst_buf(ctx);

	/* Source (stream) buffer. */
	src_dma = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	vdpu_write_relaxed(vpu, src_dma, G1_REG_ADDR_STR);

	/* Destination (decoded frame) buffer. */
	dst_dma = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	vdpu_write_relaxed(vpu, dst_dma, G1_REG_ADDR_DST);

	/* Higher profiles require DMV buffer appended to reference frames. */
	if (ctrls->sps->profile_idc > 66) {
		size_t pic_size = ctx->h264_dec.pic_size;
		size_t mv_offset = round_up(pic_size, 8);

		if (ctrls->slices[0].flags & V4L2_H264_SLICE_FLAG_BOTTOM_FIELD)
			mv_offset += 32 * H264_MB_WIDTH(ctx->dst_fmt.width);

		vdpu_write_relaxed(vpu, dst_dma + mv_offset,
				   G1_REG_ADDR_DIR_MV);
	}

	/* Auxiliary buffer prepared in hantro_g1_h264_dec_prepare_table(). */
	vdpu_write_relaxed(vpu, ctx->h264_dec.priv.dma, G1_REG_ADDR_QTABLE);
}