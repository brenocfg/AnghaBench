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
struct vdoa_q_data {scalar_t__ pixelformat; int height; int width; int bytesperline; } ;
struct vdoa_data {scalar_t__ regs; struct vdoa_ctx* curr_ctx; } ;
struct vdoa_ctx {struct vdoa_q_data* q_data; int /*<<< orphan*/  submitted_job; int /*<<< orphan*/  completion; struct vdoa_data* vdoa; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 scalar_t__ V4L2_PIX_FMT_NV21 ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 scalar_t__ VDOAC ; 
 int VDOAC_PFS ; 
 scalar_t__ VDOAFP ; 
 scalar_t__ VDOAIE ; 
 scalar_t__ VDOAIEBA00 ; 
 int VDOAIE_EIEOT ; 
 int VDOAIE_EITERR ; 
 scalar_t__ VDOAIUBO ; 
 scalar_t__ VDOASL ; 
 scalar_t__ VDOASRR ; 
 int VDOASRR_START ; 
 scalar_t__ VDOAVEBA0 ; 
 scalar_t__ VDOAVUBO ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  vdoa_wait_for_completion (struct vdoa_ctx*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void vdoa_device_run(struct vdoa_ctx *ctx, dma_addr_t dst, dma_addr_t src)
{
	struct vdoa_q_data *src_q_data, *dst_q_data;
	struct vdoa_data *vdoa = ctx->vdoa;
	u32 val;

	if (vdoa->curr_ctx)
		vdoa_wait_for_completion(vdoa->curr_ctx);

	vdoa->curr_ctx = ctx;

	reinit_completion(&ctx->completion);
	ctx->submitted_job++;

	src_q_data = &ctx->q_data[V4L2_M2M_SRC];
	dst_q_data = &ctx->q_data[V4L2_M2M_DST];

	/* Progressive, no sync, 1 frame per run */
	if (dst_q_data->pixelformat == V4L2_PIX_FMT_YUYV)
		val = VDOAC_PFS;
	else
		val = 0;
	writel(val, vdoa->regs + VDOAC);

	writel(dst_q_data->height << 16 | dst_q_data->width,
	       vdoa->regs + VDOAFP);

	val = dst;
	writel(val, vdoa->regs + VDOAIEBA00);

	writel(src_q_data->bytesperline << 16 | dst_q_data->bytesperline,
	       vdoa->regs + VDOASL);

	if (dst_q_data->pixelformat == V4L2_PIX_FMT_NV12 ||
	    dst_q_data->pixelformat == V4L2_PIX_FMT_NV21)
		val = dst_q_data->bytesperline * dst_q_data->height;
	else
		val = 0;
	writel(val, vdoa->regs + VDOAIUBO);

	val = src;
	writel(val, vdoa->regs + VDOAVEBA0);
	val = round_up(src_q_data->bytesperline * src_q_data->height, 4096);
	writel(val, vdoa->regs + VDOAVUBO);

	/* Enable interrupts and start transfer */
	writel(VDOAIE_EITERR | VDOAIE_EIEOT, vdoa->regs + VDOAIE);
	writel(VDOASRR_START, vdoa->regs + VDOASRR);
}