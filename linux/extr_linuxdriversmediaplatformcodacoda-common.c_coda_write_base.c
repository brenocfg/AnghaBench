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
typedef  int u32 ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct coda_q_data {int fourcc; int bytesperline; int height; } ;
struct coda_ctx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_NV12 132 
#define  V4L2_PIX_FMT_YUV420 131 
#define  V4L2_PIX_FMT_YUV422P 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVU420 128 
 int /*<<< orphan*/  coda_write (int /*<<< orphan*/ ,int,unsigned int) ; 
 int vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void coda_write_base(struct coda_ctx *ctx, struct coda_q_data *q_data,
		     struct vb2_v4l2_buffer *buf, unsigned int reg_y)
{
	u32 base_y = vb2_dma_contig_plane_dma_addr(&buf->vb2_buf, 0);
	u32 base_cb, base_cr;

	switch (q_data->fourcc) {
	case V4L2_PIX_FMT_YUYV:
		/* Fallthrough: IN -H264-> CODA -NV12 MB-> VDOA -YUYV-> OUT */
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_YUV420:
	default:
		base_cb = base_y + q_data->bytesperline * q_data->height;
		base_cr = base_cb + q_data->bytesperline * q_data->height / 4;
		break;
	case V4L2_PIX_FMT_YVU420:
		/* Switch Cb and Cr for YVU420 format */
		base_cr = base_y + q_data->bytesperline * q_data->height;
		base_cb = base_cr + q_data->bytesperline * q_data->height / 4;
		break;
	case V4L2_PIX_FMT_YUV422P:
		base_cb = base_y + q_data->bytesperline * q_data->height;
		base_cr = base_cb + q_data->bytesperline * q_data->height / 2;
	}

	coda_write(ctx->dev, base_y, reg_y);
	coda_write(ctx->dev, base_cb, reg_y + 4);
	coda_write(ctx->dev, base_cr, reg_y + 8);
}