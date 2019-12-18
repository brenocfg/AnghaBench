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
struct cedrus_run {int dummy; } ;
struct cedrus_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  neighbor_info_buf_dma; int /*<<< orphan*/  pic_info_buf_dma; } ;
struct TYPE_4__ {TYPE_1__ h264; } ;
struct cedrus_ctx {TYPE_2__ codec; struct cedrus_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEDRUS_CODEC_H264 ; 
 int /*<<< orphan*/  VE_H264_EXTRA_BUFFER1 ; 
 int /*<<< orphan*/  VE_H264_EXTRA_BUFFER2 ; 
 int /*<<< orphan*/  VE_H264_SDROT_CTRL ; 
 int /*<<< orphan*/  cedrus_engine_enable (struct cedrus_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cedrus_set_params (struct cedrus_ctx*,struct cedrus_run*) ; 
 int /*<<< orphan*/  cedrus_write (struct cedrus_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cedrus_write_frame_list (struct cedrus_ctx*,struct cedrus_run*) ; 
 int /*<<< orphan*/  cedrus_write_scaling_lists (struct cedrus_ctx*,struct cedrus_run*) ; 

__attribute__((used)) static void cedrus_h264_setup(struct cedrus_ctx *ctx,
			      struct cedrus_run *run)
{
	struct cedrus_dev *dev = ctx->dev;

	cedrus_engine_enable(dev, CEDRUS_CODEC_H264);

	cedrus_write(dev, VE_H264_SDROT_CTRL, 0);
	cedrus_write(dev, VE_H264_EXTRA_BUFFER1,
		     ctx->codec.h264.pic_info_buf_dma);
	cedrus_write(dev, VE_H264_EXTRA_BUFFER2,
		     ctx->codec.h264.neighbor_info_buf_dma);

	cedrus_write_scaling_lists(ctx, run);
	cedrus_write_frame_list(ctx, run);

	cedrus_set_params(ctx, run);
}