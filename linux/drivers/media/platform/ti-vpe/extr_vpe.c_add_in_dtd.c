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
struct TYPE_4__ {int width; int height; } ;
struct vpe_q_data {int nplanes; int* bytesperline; int height; int flags; int width; TYPE_2__ c_rect; struct vpe_fmt* fmt; } ;
struct vpe_port_data {size_t vb_index; int vb_part; int /*<<< orphan*/  channel; } ;
struct vpe_fmt {scalar_t__ fourcc; struct vpdma_data_format** vpdma_fmt; scalar_t__ coplanar; } ;
struct vpe_ctx {int src_mv_buf_selector; int* mv_buf_dma; int sequence; int /*<<< orphan*/  desc_list; int /*<<< orphan*/  dev; TYPE_1__** src_vbs; struct vpe_q_data* q_data; } ;
struct vpdma_data_format {int depth; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  field; } ;
struct vb2_buffer {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_3__ {struct vb2_buffer vb2_buf; } ;

/* Variables and functions */
 int Q_DATA_FRAME_1D ; 
 int Q_DATA_INTERLACED_SEQ_TB ; 
 int Q_DATA_MODE_TILED ; 
 size_t Q_DATA_SRC ; 
 int /*<<< orphan*/  V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 size_t VPDMA_DATA_FMT_MV ; 
 int VPDMA_DATA_FRAME_1D ; 
 int VPDMA_DATA_MODE_TILED ; 
 size_t VPE_LUMA ; 
 int VPE_PORT_MV_IN ; 
 struct vpe_port_data* port_data ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int) ; 
 int /*<<< orphan*/  vpdma_add_in_dtd (int /*<<< orphan*/ *,int,int,TYPE_2__*,struct vpdma_data_format const*,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vpdma_data_format* vpdma_misc_fmts ; 
 int /*<<< orphan*/  vpe_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void add_in_dtd(struct vpe_ctx *ctx, int port)
{
	struct vpe_q_data *q_data = &ctx->q_data[Q_DATA_SRC];
	const struct vpe_port_data *p_data = &port_data[port];
	struct vb2_buffer *vb = &ctx->src_vbs[p_data->vb_index]->vb2_buf;
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vpe_fmt *fmt = q_data->fmt;
	const struct vpdma_data_format *vpdma_fmt;
	int mv_buf_selector = ctx->src_mv_buf_selector;
	int field = vbuf->field == V4L2_FIELD_BOTTOM;
	int frame_width, frame_height;
	dma_addr_t dma_addr;
	u32 flags = 0;
	u32 offset = 0;

	if (port == VPE_PORT_MV_IN) {
		vpdma_fmt = &vpdma_misc_fmts[VPDMA_DATA_FMT_MV];
		dma_addr = ctx->mv_buf_dma[mv_buf_selector];
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

		if (q_data->flags & Q_DATA_INTERLACED_SEQ_TB) {
			/*
			 * Use top or bottom field from same vb alternately
			 * f,f-1,f-2 = TBT when seq is even
			 * f,f-1,f-2 = BTB when seq is odd
			 */
			field = (p_data->vb_index + (ctx->sequence % 2)) % 2;

			if (field) {
				/*
				 * bottom field of a SEQ_TB buffer
				 * Skip the top field data by
				 */
				int height = q_data->height / 2;
				int bpp = fmt->fourcc == V4L2_PIX_FMT_NV12 ?
						1 : (vpdma_fmt->depth >> 3);
				if (plane)
					height /= 2;
				dma_addr += q_data->width * height * bpp;
			}
		}
	}

	if (q_data->flags & Q_DATA_FRAME_1D)
		flags |= VPDMA_DATA_FRAME_1D;
	if (q_data->flags & Q_DATA_MODE_TILED)
		flags |= VPDMA_DATA_MODE_TILED;

	frame_width = q_data->c_rect.width;
	frame_height = q_data->c_rect.height;

	if (p_data->vb_part && fmt->fourcc == V4L2_PIX_FMT_NV12)
		frame_height /= 2;

	vpdma_add_in_dtd(&ctx->desc_list, q_data->width,
			 q_data->bytesperline[VPE_LUMA], &q_data->c_rect,
		vpdma_fmt, dma_addr, p_data->channel, field, flags, frame_width,
		frame_height, 0, 0);
}