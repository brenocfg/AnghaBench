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
typedef  int u32 ;
struct vpe_q_data {int nplanes; int* bytesperline; int height; int flags; int /*<<< orphan*/  c_rect; int /*<<< orphan*/  width; struct vpe_fmt* fmt; } ;
struct vpe_port_data {int vb_part; int /*<<< orphan*/  channel; } ;
struct vpe_fmt {struct vpdma_data_format** vpdma_fmt; scalar_t__ coplanar; } ;
struct vpe_ctx {int* mv_buf_dma; int /*<<< orphan*/  desc_list; TYPE_2__* dev; struct vpe_q_data* q_data; int /*<<< orphan*/  src_mv_buf_selector; TYPE_1__* dst_vb; } ;
struct vpdma_data_format {int dummy; } ;
struct vb2_buffer {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  vpdma; } ;
struct TYPE_3__ {struct vb2_buffer vb2_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_H ; 
 int /*<<< orphan*/  MAX_OUT_HEIGHT_REG1 ; 
 int /*<<< orphan*/  MAX_OUT_WIDTH_REG1 ; 
 int /*<<< orphan*/  MAX_W ; 
 size_t Q_DATA_DST ; 
 int Q_DATA_FRAME_1D ; 
 int Q_DATA_MODE_TILED ; 
 size_t Q_DATA_SRC ; 
 size_t VPDMA_DATA_FMT_MV ; 
 int VPDMA_DATA_FRAME_1D ; 
 int VPDMA_DATA_MODE_TILED ; 
 int /*<<< orphan*/  VPDMA_MAX_SIZE1 ; 
 size_t VPE_LUMA ; 
 int VPE_PORT_MV_OUT ; 
 struct vpe_port_data* port_data ; 
 int vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int) ; 
 int /*<<< orphan*/  vpdma_add_out_dtd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct vpdma_data_format const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vpdma_data_format* vpdma_misc_fmts ; 
 int /*<<< orphan*/  vpdma_set_max_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpe_err (TYPE_2__*,char*,int) ; 

__attribute__((used)) static void add_out_dtd(struct vpe_ctx *ctx, int port)
{
	struct vpe_q_data *q_data = &ctx->q_data[Q_DATA_DST];
	const struct vpe_port_data *p_data = &port_data[port];
	struct vb2_buffer *vb = &ctx->dst_vb->vb2_buf;
	struct vpe_fmt *fmt = q_data->fmt;
	const struct vpdma_data_format *vpdma_fmt;
	int mv_buf_selector = !ctx->src_mv_buf_selector;
	dma_addr_t dma_addr;
	u32 flags = 0;
	u32 offset = 0;

	if (port == VPE_PORT_MV_OUT) {
		vpdma_fmt = &vpdma_misc_fmts[VPDMA_DATA_FMT_MV];
		dma_addr = ctx->mv_buf_dma[mv_buf_selector];
		q_data = &ctx->q_data[Q_DATA_SRC];
	} else {
		/* to incorporate interleaved formats */
		int plane = fmt->coplanar ? p_data->vb_part : 0;

		vpdma_fmt = fmt->vpdma_fmt[plane];
		/*
		 * If we are using a single plane buffer and
		 * we need to set a separate vpdma chroma channel.
		 */
		if (q_data->nplanes == 1 && plane) {
			dma_addr = vb2_dma_contig_plane_dma_addr(vb, 0);
			/* Compute required offset */
			offset = q_data->bytesperline[0] * q_data->height;
		} else {
			dma_addr = vb2_dma_contig_plane_dma_addr(vb, plane);
			/* Use address as is, no offset */
			offset = 0;
		}
		if (!dma_addr) {
			vpe_err(ctx->dev,
				"acquiring output buffer(%d) dma_addr failed\n",
				port);
			return;
		}
		/* Apply the offset */
		dma_addr += offset;
	}

	if (q_data->flags & Q_DATA_FRAME_1D)
		flags |= VPDMA_DATA_FRAME_1D;
	if (q_data->flags & Q_DATA_MODE_TILED)
		flags |= VPDMA_DATA_MODE_TILED;

	vpdma_set_max_size(ctx->dev->vpdma, VPDMA_MAX_SIZE1,
			   MAX_W, MAX_H);

	vpdma_add_out_dtd(&ctx->desc_list, q_data->width,
			  q_data->bytesperline[VPE_LUMA], &q_data->c_rect,
			  vpdma_fmt, dma_addr, MAX_OUT_WIDTH_REG1,
			  MAX_OUT_HEIGHT_REG1, p_data->channel, flags);
}