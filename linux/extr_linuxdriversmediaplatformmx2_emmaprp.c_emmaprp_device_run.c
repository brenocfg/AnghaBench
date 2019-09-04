#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int u32 ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct emmaprp_q_data {unsigned int width; unsigned int height; } ;
struct emmaprp_dev {scalar_t__ base_emma; int /*<<< orphan*/  v4l2_dev; } ;
struct emmaprp_ctx {int /*<<< orphan*/  m2m_ctx; struct emmaprp_dev* dev; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 scalar_t__ PRP_CH2_OUT_IMAGE_SIZE ; 
 scalar_t__ PRP_CNTL ; 
 unsigned int PRP_CNTL_CH2EN ; 
 unsigned int PRP_CNTL_CH2_OUT_YUV420 ; 
 unsigned int PRP_CNTL_DATA_IN_YUV422 ; 
 scalar_t__ PRP_DEST_CB_PTR ; 
 scalar_t__ PRP_DEST_CR_PTR ; 
 scalar_t__ PRP_DEST_Y_PTR ; 
 unsigned int PRP_INTR_CH2FC ; 
 unsigned int PRP_INTR_CH2WERR ; 
 scalar_t__ PRP_INTR_CNTL ; 
 unsigned int PRP_INTR_RDERR ; 
 unsigned int PRP_SIZE_HEIGHT (unsigned int) ; 
 unsigned int PRP_SIZE_WIDTH (unsigned int) ; 
 scalar_t__ PRP_SOURCE_Y_PTR ; 
 scalar_t__ PRP_SRC_FRAME_SIZE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  emmaprp_dump_regs (struct emmaprp_dev*) ; 
 struct emmaprp_q_data* get_q_data (struct emmaprp_ctx*,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 unsigned int vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void emmaprp_device_run(void *priv)
{
	struct emmaprp_ctx *ctx = priv;
	struct emmaprp_q_data *s_q_data, *d_q_data;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	struct emmaprp_dev *pcdev = ctx->dev;
	unsigned int s_width, s_height;
	unsigned int d_width, d_height;
	unsigned int d_size;
	dma_addr_t p_in, p_out;
	u32 tmp;

	src_buf = v4l2_m2m_next_src_buf(ctx->m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->m2m_ctx);

	s_q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	s_width	= s_q_data->width;
	s_height = s_q_data->height;

	d_q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	d_width = d_q_data->width;
	d_height = d_q_data->height;
	d_size = d_width * d_height;

	p_in = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	p_out = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	if (!p_in || !p_out) {
		v4l2_err(&pcdev->v4l2_dev,
			 "Acquiring kernel pointers to buffers failed\n");
		return;
	}

	/* Input frame parameters */
	writel(p_in, pcdev->base_emma + PRP_SOURCE_Y_PTR);
	writel(PRP_SIZE_WIDTH(s_width) | PRP_SIZE_HEIGHT(s_height),
	       pcdev->base_emma + PRP_SRC_FRAME_SIZE);

	/* Output frame parameters */
	writel(p_out, pcdev->base_emma + PRP_DEST_Y_PTR);
	writel(p_out + d_size, pcdev->base_emma + PRP_DEST_CB_PTR);
	writel(p_out + d_size + (d_size >> 2),
	       pcdev->base_emma + PRP_DEST_CR_PTR);
	writel(PRP_SIZE_WIDTH(d_width) | PRP_SIZE_HEIGHT(d_height),
	       pcdev->base_emma + PRP_CH2_OUT_IMAGE_SIZE);

	/* IRQ configuration */
	tmp = readl(pcdev->base_emma + PRP_INTR_CNTL);
	writel(tmp | PRP_INTR_RDERR |
		PRP_INTR_CH2WERR |
		PRP_INTR_CH2FC,
		pcdev->base_emma + PRP_INTR_CNTL);

	emmaprp_dump_regs(pcdev);

	/* Enable transfer */
	tmp = readl(pcdev->base_emma + PRP_CNTL);
	writel(tmp | PRP_CNTL_CH2_OUT_YUV420 |
		PRP_CNTL_DATA_IN_YUV422 |
		PRP_CNTL_CH2EN,
		pcdev->base_emma + PRP_CNTL);
}