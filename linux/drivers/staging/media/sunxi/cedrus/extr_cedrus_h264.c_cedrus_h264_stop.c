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
struct cedrus_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  pic_info_buf_dma; int /*<<< orphan*/  pic_info_buf; int /*<<< orphan*/  neighbor_info_buf_dma; int /*<<< orphan*/  neighbor_info_buf; int /*<<< orphan*/  mv_col_buf_dma; int /*<<< orphan*/  mv_col_buf; int /*<<< orphan*/  mv_col_buf_size; } ;
struct TYPE_3__ {TYPE_2__ h264; } ;
struct cedrus_ctx {TYPE_1__ codec; struct cedrus_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEDRUS_NEIGHBOR_INFO_BUF_SIZE ; 
 int /*<<< orphan*/  CEDRUS_PIC_INFO_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cedrus_h264_stop(struct cedrus_ctx *ctx)
{
	struct cedrus_dev *dev = ctx->dev;

	dma_free_coherent(dev->dev, ctx->codec.h264.mv_col_buf_size,
			  ctx->codec.h264.mv_col_buf,
			  ctx->codec.h264.mv_col_buf_dma);
	dma_free_coherent(dev->dev, CEDRUS_NEIGHBOR_INFO_BUF_SIZE,
			  ctx->codec.h264.neighbor_info_buf,
			  ctx->codec.h264.neighbor_info_buf_dma);
	dma_free_coherent(dev->dev, CEDRUS_PIC_INFO_BUF_SIZE,
			  ctx->codec.h264.pic_info_buf,
			  ctx->codec.h264.pic_info_buf_dma);
}