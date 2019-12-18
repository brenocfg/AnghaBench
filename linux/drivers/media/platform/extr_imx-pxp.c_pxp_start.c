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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; int /*<<< orphan*/  field; int /*<<< orphan*/  timecode; TYPE_3__ vb2_buf; scalar_t__ sequence; } ;
struct pxp_q_data {int /*<<< orphan*/  sequence; } ;
struct pxp_dev {scalar_t__ mmio; int /*<<< orphan*/  v4l2_dev; } ;
struct pxp_ctx {int mode; int /*<<< orphan*/  alpha_component; TYPE_2__* q_data; struct pxp_dev* dev; } ;
typedef  int dma_addr_t ;
struct TYPE_5__ {int width; int height; int bytesperline; TYPE_1__* fmt; } ;
struct TYPE_4__ {int fourcc; } ;

/* Variables and functions */
 int BF_PXP_CTRL_HFLIP0 (int) ; 
 int BF_PXP_CTRL_VFLIP0 (int) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX0_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX10_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX11_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX12_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX13_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX14_SEL (int) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX15_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX1_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX2_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX3_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX4_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX5_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX6_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX7_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX8_SEL (int /*<<< orphan*/ ) ; 
 int BF_PXP_DATA_PATH_CTRL0_MUX9_SEL (int) ; 
 int BF_PXP_DATA_PATH_CTRL1_MUX16_SEL (int) ; 
 int BF_PXP_DATA_PATH_CTRL1_MUX17_SEL (int) ; 
 int BF_PXP_OUT_AS_LRC_X (int /*<<< orphan*/ ) ; 
 int BF_PXP_OUT_AS_LRC_Y (int /*<<< orphan*/ ) ; 
 int BF_PXP_OUT_AS_ULC_X (int) ; 
 int BF_PXP_OUT_AS_ULC_Y (int) ; 
 int BF_PXP_OUT_CTRL_ALPHA (int /*<<< orphan*/ ) ; 
 int BF_PXP_OUT_CTRL_ALPHA_OUTPUT (int) ; 
 int BF_PXP_OUT_LRC_X (int) ; 
 int BF_PXP_OUT_LRC_Y (int) ; 
 int BF_PXP_OUT_PITCH_PITCH (int) ; 
 int BF_PXP_OUT_PS_LRC_X (int) ; 
 int BF_PXP_OUT_PS_LRC_Y (int) ; 
 int BF_PXP_OUT_PS_ULC_X (int /*<<< orphan*/ ) ; 
 int BF_PXP_OUT_PS_ULC_Y (int /*<<< orphan*/ ) ; 
 int BF_PXP_PS_CTRL_DECX (int) ; 
 int BF_PXP_PS_CTRL_DECY (int) ; 
 int BF_PXP_PS_OFFSET_XOFFSET (int /*<<< orphan*/ ) ; 
 int BF_PXP_PS_OFFSET_YOFFSET (int /*<<< orphan*/ ) ; 
 int BF_PXP_PS_PITCH_PITCH (int) ; 
 int BF_PXP_PS_SCALE_XSCALE (int) ; 
 int BF_PXP_PS_SCALE_YSCALE (int) ; 
 int BM_PXP_CTRL_ENABLE ; 
 int BM_PXP_CTRL_ENABLE_CSC2 ; 
 int BM_PXP_CTRL_ENABLE_LUT ; 
 int BM_PXP_CTRL_ENABLE_PS_AS_OUT ; 
 int BM_PXP_CTRL_ENABLE_ROTATE0 ; 
 int BM_PXP_CTRL_IRQ_ENABLE ; 
 int BM_PXP_LUT_CTRL_BYPASS ; 
 int EFAULT ; 
 scalar_t__ HW_PXP_AS_CLRKEYHIGH_0 ; 
 scalar_t__ HW_PXP_AS_CLRKEYLOW_0 ; 
 scalar_t__ HW_PXP_CTRL ; 
 scalar_t__ HW_PXP_CTRL_SET ; 
 scalar_t__ HW_PXP_DATA_PATH_CTRL0 ; 
 scalar_t__ HW_PXP_DATA_PATH_CTRL1 ; 
 scalar_t__ HW_PXP_IRQ_MASK ; 
 scalar_t__ HW_PXP_LUT_CTRL ; 
 scalar_t__ HW_PXP_OUT_AS_LRC ; 
 scalar_t__ HW_PXP_OUT_AS_ULC ; 
 scalar_t__ HW_PXP_OUT_BUF ; 
 scalar_t__ HW_PXP_OUT_BUF2 ; 
 scalar_t__ HW_PXP_OUT_CTRL ; 
 scalar_t__ HW_PXP_OUT_LRC ; 
 scalar_t__ HW_PXP_OUT_PITCH ; 
 scalar_t__ HW_PXP_OUT_PS_LRC ; 
 scalar_t__ HW_PXP_OUT_PS_ULC ; 
 scalar_t__ HW_PXP_PS_BACKGROUND_0 ; 
 scalar_t__ HW_PXP_PS_BUF ; 
 scalar_t__ HW_PXP_PS_CLRKEYHIGH_0 ; 
 scalar_t__ HW_PXP_PS_CLRKEYLOW_0 ; 
 scalar_t__ HW_PXP_PS_CTRL ; 
 scalar_t__ HW_PXP_PS_OFFSET ; 
 scalar_t__ HW_PXP_PS_PITCH ; 
 scalar_t__ HW_PXP_PS_SCALE ; 
 scalar_t__ HW_PXP_PS_UBUF ; 
 scalar_t__ HW_PXP_PS_VBUF ; 
 int MEM2MEM_HFLIP ; 
 int MEM2MEM_VFLIP ; 
 int V4L2_BUF_FLAG_BFRAME ; 
 int V4L2_BUF_FLAG_KEYFRAME ; 
 int V4L2_BUF_FLAG_PFRAME ; 
 int V4L2_BUF_FLAG_TIMECODE ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
#define  V4L2_PIX_FMT_GREY 139 
#define  V4L2_PIX_FMT_NV12 138 
#define  V4L2_PIX_FMT_NV16 137 
#define  V4L2_PIX_FMT_NV21 136 
#define  V4L2_PIX_FMT_NV61 135 
#define  V4L2_PIX_FMT_UYVY 134 
#define  V4L2_PIX_FMT_VYUY 133 
#define  V4L2_PIX_FMT_Y4 132 
#define  V4L2_PIX_FMT_YUV420 131 
#define  V4L2_PIX_FMT_YUV422P 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 
 struct pxp_q_data* get_q_data (struct pxp_ctx*,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  pxp_setup_csc (struct pxp_ctx*) ; 
 int pxp_v4l2_pix_fmt_to_out_format (int) ; 
 int pxp_v4l2_pix_fmt_to_ps_format (int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int vb2_dma_contig_plane_dma_addr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pxp_start(struct pxp_ctx *ctx, struct vb2_v4l2_buffer *in_vb,
		     struct vb2_v4l2_buffer *out_vb)
{
	struct pxp_dev *dev = ctx->dev;
	struct pxp_q_data *q_data;
	u32 src_width, src_height, src_stride, src_fourcc;
	u32 dst_width, dst_height, dst_stride, dst_fourcc;
	dma_addr_t p_in, p_out;
	u32 ctrl, out_ctrl, out_buf, out_buf2, out_pitch, out_lrc, out_ps_ulc;
	u32 out_ps_lrc;
	u32 ps_ctrl, ps_buf, ps_ubuf, ps_vbuf, ps_pitch, ps_scale, ps_offset;
	u32 as_ulc, as_lrc;
	u32 y_size;
	u32 decx, decy, xscale, yscale;

	q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);

	src_width = ctx->q_data[V4L2_M2M_SRC].width;
	dst_width = ctx->q_data[V4L2_M2M_DST].width;
	src_height = ctx->q_data[V4L2_M2M_SRC].height;
	dst_height = ctx->q_data[V4L2_M2M_DST].height;
	src_stride = ctx->q_data[V4L2_M2M_SRC].bytesperline;
	dst_stride = ctx->q_data[V4L2_M2M_DST].bytesperline;
	src_fourcc = ctx->q_data[V4L2_M2M_SRC].fmt->fourcc;
	dst_fourcc = ctx->q_data[V4L2_M2M_DST].fmt->fourcc;

	p_in = vb2_dma_contig_plane_dma_addr(&in_vb->vb2_buf, 0);
	p_out = vb2_dma_contig_plane_dma_addr(&out_vb->vb2_buf, 0);

	if (!p_in || !p_out) {
		v4l2_err(&dev->v4l2_dev,
			 "Acquiring DMA addresses of buffers failed\n");
		return -EFAULT;
	}

	out_vb->sequence =
		get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE)->sequence++;
	in_vb->sequence = q_data->sequence++;
	out_vb->vb2_buf.timestamp = in_vb->vb2_buf.timestamp;

	if (in_vb->flags & V4L2_BUF_FLAG_TIMECODE)
		out_vb->timecode = in_vb->timecode;
	out_vb->field = in_vb->field;
	out_vb->flags = in_vb->flags &
		(V4L2_BUF_FLAG_TIMECODE |
		 V4L2_BUF_FLAG_KEYFRAME |
		 V4L2_BUF_FLAG_PFRAME |
		 V4L2_BUF_FLAG_BFRAME |
		 V4L2_BUF_FLAG_TSTAMP_SRC_MASK);

	/* Rotation disabled, 8x8 block size */
	ctrl = BF_PXP_CTRL_VFLIP0(!!(ctx->mode & MEM2MEM_VFLIP)) |
	       BF_PXP_CTRL_HFLIP0(!!(ctx->mode & MEM2MEM_HFLIP));
	/* Always write alpha value as V4L2_CID_ALPHA_COMPONENT */
	out_ctrl = BF_PXP_OUT_CTRL_ALPHA(ctx->alpha_component) |
		   BF_PXP_OUT_CTRL_ALPHA_OUTPUT(1) |
		   pxp_v4l2_pix_fmt_to_out_format(dst_fourcc);
	out_buf = p_out;
	switch (dst_fourcc) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		out_buf2 = out_buf + dst_stride * dst_height;
		break;
	default:
		out_buf2 = 0;
	}

	out_pitch = BF_PXP_OUT_PITCH_PITCH(dst_stride);
	out_lrc = BF_PXP_OUT_LRC_X(dst_width - 1) |
		  BF_PXP_OUT_LRC_Y(dst_height - 1);
	/* PS covers whole output */
	out_ps_ulc = BF_PXP_OUT_PS_ULC_X(0) | BF_PXP_OUT_PS_ULC_Y(0);
	out_ps_lrc = BF_PXP_OUT_PS_LRC_X(dst_width - 1) |
		     BF_PXP_OUT_PS_LRC_Y(dst_height - 1);
	/* no AS */
	as_ulc = BF_PXP_OUT_AS_ULC_X(1) | BF_PXP_OUT_AS_ULC_Y(1);
	as_lrc = BF_PXP_OUT_AS_LRC_X(0) | BF_PXP_OUT_AS_LRC_Y(0);

	decx = (src_width <= dst_width) ? 0 : ilog2(src_width / dst_width);
	decy = (src_height <= dst_height) ? 0 : ilog2(src_height / dst_height);
	ps_ctrl = BF_PXP_PS_CTRL_DECX(decx) | BF_PXP_PS_CTRL_DECY(decy) |
		  pxp_v4l2_pix_fmt_to_ps_format(src_fourcc);
	ps_buf = p_in;
	y_size = src_stride * src_height;
	switch (src_fourcc) {
	case V4L2_PIX_FMT_YUV420:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = ps_ubuf + y_size / 4;
		break;
	case V4L2_PIX_FMT_YUV422P:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = ps_ubuf + y_size / 2;
		break;
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = 0;
		break;
	case V4L2_PIX_FMT_GREY:
	case V4L2_PIX_FMT_Y4:
		ps_ubuf = 0;
		/* In grayscale mode, ps_vbuf contents are reused as CbCr */
		ps_vbuf = 0x8080;
		break;
	default:
		ps_ubuf = 0;
		ps_vbuf = 0;
		break;
	}
	ps_pitch = BF_PXP_PS_PITCH_PITCH(src_stride);
	if (decx) {
		xscale = (src_width >> decx) * 0x1000 / dst_width;
	} else {
		switch (src_fourcc) {
		case V4L2_PIX_FMT_UYVY:
		case V4L2_PIX_FMT_YUYV:
		case V4L2_PIX_FMT_VYUY:
		case V4L2_PIX_FMT_YVYU:
		case V4L2_PIX_FMT_NV16:
		case V4L2_PIX_FMT_NV12:
		case V4L2_PIX_FMT_NV21:
		case V4L2_PIX_FMT_NV61:
		case V4L2_PIX_FMT_YUV422P:
		case V4L2_PIX_FMT_YUV420:
			/*
			 * This avoids sampling past the right edge for
			 * horizontally chroma subsampled formats.
			 */
			xscale = (src_width - 2) * 0x1000 / (dst_width - 1);
			break;
		default:
			xscale = (src_width - 1) * 0x1000 / (dst_width - 1);
			break;
		}
	}
	if (decy)
		yscale = (src_height >> decy) * 0x1000 / dst_height;
	else
		yscale = (src_height - 1) * 0x1000 / (dst_height - 1);
	ps_scale = BF_PXP_PS_SCALE_YSCALE(yscale) |
		   BF_PXP_PS_SCALE_XSCALE(xscale);
	ps_offset = BF_PXP_PS_OFFSET_YOFFSET(0) | BF_PXP_PS_OFFSET_XOFFSET(0);

	writel(ctrl, dev->mmio + HW_PXP_CTRL);
	/* skip STAT */
	writel(out_ctrl, dev->mmio + HW_PXP_OUT_CTRL);
	writel(out_buf, dev->mmio + HW_PXP_OUT_BUF);
	writel(out_buf2, dev->mmio + HW_PXP_OUT_BUF2);
	writel(out_pitch, dev->mmio + HW_PXP_OUT_PITCH);
	writel(out_lrc, dev->mmio + HW_PXP_OUT_LRC);
	writel(out_ps_ulc, dev->mmio + HW_PXP_OUT_PS_ULC);
	writel(out_ps_lrc, dev->mmio + HW_PXP_OUT_PS_LRC);
	writel(as_ulc, dev->mmio + HW_PXP_OUT_AS_ULC);
	writel(as_lrc, dev->mmio + HW_PXP_OUT_AS_LRC);
	writel(ps_ctrl, dev->mmio + HW_PXP_PS_CTRL);
	writel(ps_buf, dev->mmio + HW_PXP_PS_BUF);
	writel(ps_ubuf, dev->mmio + HW_PXP_PS_UBUF);
	writel(ps_vbuf, dev->mmio + HW_PXP_PS_VBUF);
	writel(ps_pitch, dev->mmio + HW_PXP_PS_PITCH);
	writel(0x00ffffff, dev->mmio + HW_PXP_PS_BACKGROUND_0);
	writel(ps_scale, dev->mmio + HW_PXP_PS_SCALE);
	writel(ps_offset, dev->mmio + HW_PXP_PS_OFFSET);
	/* disable processed surface color keying */
	writel(0x00ffffff, dev->mmio + HW_PXP_PS_CLRKEYLOW_0);
	writel(0x00000000, dev->mmio + HW_PXP_PS_CLRKEYHIGH_0);

	/* disable alpha surface color keying */
	writel(0x00ffffff, dev->mmio + HW_PXP_AS_CLRKEYLOW_0);
	writel(0x00000000, dev->mmio + HW_PXP_AS_CLRKEYHIGH_0);

	/* setup CSC */
	pxp_setup_csc(ctx);

	/* bypass LUT */
	writel(BM_PXP_LUT_CTRL_BYPASS, dev->mmio + HW_PXP_LUT_CTRL);

	writel(BF_PXP_DATA_PATH_CTRL0_MUX15_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX14_SEL(1)|
	       BF_PXP_DATA_PATH_CTRL0_MUX13_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX12_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX11_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX10_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX9_SEL(1)|
	       BF_PXP_DATA_PATH_CTRL0_MUX8_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX7_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX6_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX5_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX4_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX3_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX2_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX1_SEL(0)|
	       BF_PXP_DATA_PATH_CTRL0_MUX0_SEL(0),
	       dev->mmio + HW_PXP_DATA_PATH_CTRL0);
	writel(BF_PXP_DATA_PATH_CTRL1_MUX17_SEL(1) |
	       BF_PXP_DATA_PATH_CTRL1_MUX16_SEL(1),
	       dev->mmio + HW_PXP_DATA_PATH_CTRL1);

	writel(0xffff, dev->mmio + HW_PXP_IRQ_MASK);

	/* ungate, enable PS/AS/OUT and PXP operation */
	writel(BM_PXP_CTRL_IRQ_ENABLE, dev->mmio + HW_PXP_CTRL_SET);
	writel(BM_PXP_CTRL_ENABLE | BM_PXP_CTRL_ENABLE_CSC2 |
	       BM_PXP_CTRL_ENABLE_LUT | BM_PXP_CTRL_ENABLE_ROTATE0 |
	       BM_PXP_CTRL_ENABLE_PS_AS_OUT, dev->mmio + HW_PXP_CTRL_SET);

	return 0;
}