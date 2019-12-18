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
struct cedrus_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {unsigned int mv_col_buf_field_size; unsigned int mv_col_buf_size; int /*<<< orphan*/  pic_info_buf_dma; void* pic_info_buf; int /*<<< orphan*/  neighbor_info_buf_dma; void* neighbor_info_buf; void* mv_col_buf; int /*<<< orphan*/  mv_col_buf_dma; } ;
struct TYPE_6__ {TYPE_2__ h264; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct cedrus_ctx {TYPE_3__ codec; TYPE_1__ src_fmt; struct cedrus_dev* dev; } ;

/* Variables and functions */
 unsigned int CEDRUS_H264_FRAME_NUM ; 
 unsigned int CEDRUS_NEIGHBOR_INFO_BUF_SIZE ; 
 unsigned int CEDRUS_PIC_INFO_BUF_SIZE ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,unsigned int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cedrus_h264_start(struct cedrus_ctx *ctx)
{
	struct cedrus_dev *dev = ctx->dev;
	unsigned int field_size;
	unsigned int mv_col_size;
	int ret;

	/*
	 * FIXME: It seems that the H6 cedarX code is using a formula
	 * here based on the size of the frame, while all the older
	 * code is using a fixed size, so that might need to be
	 * changed at some point.
	 */
	ctx->codec.h264.pic_info_buf =
		dma_alloc_coherent(dev->dev, CEDRUS_PIC_INFO_BUF_SIZE,
				   &ctx->codec.h264.pic_info_buf_dma,
				   GFP_KERNEL);
	if (!ctx->codec.h264.pic_info_buf)
		return -ENOMEM;

	/*
	 * That buffer is supposed to be 16kiB in size, and be aligned
	 * on 16kiB as well. However, dma_alloc_coherent provides the
	 * guarantee that we'll have a CPU and DMA address aligned on
	 * the smallest page order that is greater to the requested
	 * size, so we don't have to overallocate.
	 */
	ctx->codec.h264.neighbor_info_buf =
		dma_alloc_coherent(dev->dev, CEDRUS_NEIGHBOR_INFO_BUF_SIZE,
				   &ctx->codec.h264.neighbor_info_buf_dma,
				   GFP_KERNEL);
	if (!ctx->codec.h264.neighbor_info_buf) {
		ret = -ENOMEM;
		goto err_pic_buf;
	}

	field_size = DIV_ROUND_UP(ctx->src_fmt.width, 16) *
		DIV_ROUND_UP(ctx->src_fmt.height, 16) * 16;

	/*
	 * FIXME: This is actually conditional to
	 * V4L2_H264_SPS_FLAG_DIRECT_8X8_INFERENCE not being set, we
	 * might have to rework this if memory efficiency ever is
	 * something we need to work on.
	 */
	field_size = field_size * 2;

	/*
	 * FIXME: This is actually conditional to
	 * V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY not being set, we might
	 * have to rework this if memory efficiency ever is something
	 * we need to work on.
	 */
	field_size = field_size * 2;
	ctx->codec.h264.mv_col_buf_field_size = field_size;

	mv_col_size = field_size * 2 * CEDRUS_H264_FRAME_NUM;
	ctx->codec.h264.mv_col_buf_size = mv_col_size;
	ctx->codec.h264.mv_col_buf = dma_alloc_coherent(dev->dev,
							ctx->codec.h264.mv_col_buf_size,
							&ctx->codec.h264.mv_col_buf_dma,
							GFP_KERNEL);
	if (!ctx->codec.h264.mv_col_buf) {
		ret = -ENOMEM;
		goto err_neighbor_buf;
	}

	return 0;

err_neighbor_buf:
	dma_free_coherent(dev->dev, CEDRUS_NEIGHBOR_INFO_BUF_SIZE,
			  ctx->codec.h264.neighbor_info_buf,
			  ctx->codec.h264.neighbor_info_buf_dma);

err_pic_buf:
	dma_free_coherent(dev->dev, CEDRUS_PIC_INFO_BUF_SIZE,
			  ctx->codec.h264.pic_info_buf,
			  ctx->codec.h264.pic_info_buf_dma);
	return ret;
}