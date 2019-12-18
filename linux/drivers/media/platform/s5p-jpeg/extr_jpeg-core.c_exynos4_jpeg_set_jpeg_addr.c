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
struct TYPE_6__ {scalar_t__ sos; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct s5p_jpeg_ctx {scalar_t__ mode; TYPE_3__ out_q; TYPE_1__ fh; struct s5p_jpeg* jpeg; } ;
struct s5p_jpeg {int /*<<< orphan*/  regs; TYPE_2__* variant; } ;
struct TYPE_5__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ S5P_JPEG_DECODE ; 
 scalar_t__ S5P_JPEG_ENCODE ; 
 scalar_t__ SJPEG_EXYNOS5433 ; 
 int /*<<< orphan*/  exynos4_jpeg_set_stream_buf_address (int /*<<< orphan*/ ,unsigned int) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 unsigned int vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos4_jpeg_set_jpeg_addr(struct s5p_jpeg_ctx *ctx)
{
	struct s5p_jpeg *jpeg = ctx->jpeg;
	struct vb2_v4l2_buffer *vb;
	unsigned int jpeg_addr = 0;

	if (ctx->mode == S5P_JPEG_ENCODE)
		vb = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	else
		vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);

	jpeg_addr = vb2_dma_contig_plane_dma_addr(&vb->vb2_buf, 0);
	if (jpeg->variant->version == SJPEG_EXYNOS5433 &&
	    ctx->mode == S5P_JPEG_DECODE)
		jpeg_addr += ctx->out_q.sos;
	exynos4_jpeg_set_stream_buf_address(jpeg->regs, jpeg_addr);
}