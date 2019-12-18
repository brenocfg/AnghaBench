#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_h264_scaling_matrix {int /*<<< orphan*/  scaling_list_4x4; int /*<<< orphan*/ * scaling_list_8x8; } ;
struct TYPE_2__ {struct v4l2_ctrl_h264_scaling_matrix* scaling_matrix; } ;
struct cedrus_run {TYPE_1__ h264; } ;
struct cedrus_dev {int dummy; } ;
struct cedrus_ctx {struct cedrus_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEDRUS_SRAM_H264_SCALING_LIST_4x4 ; 
 int /*<<< orphan*/  CEDRUS_SRAM_H264_SCALING_LIST_8x8_0 ; 
 int /*<<< orphan*/  CEDRUS_SRAM_H264_SCALING_LIST_8x8_1 ; 
 int /*<<< orphan*/  cedrus_h264_write_sram (struct cedrus_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cedrus_write_scaling_lists(struct cedrus_ctx *ctx,
				       struct cedrus_run *run)
{
	const struct v4l2_ctrl_h264_scaling_matrix *scaling =
		run->h264.scaling_matrix;
	struct cedrus_dev *dev = ctx->dev;

	cedrus_h264_write_sram(dev, CEDRUS_SRAM_H264_SCALING_LIST_8x8_0,
			       scaling->scaling_list_8x8[0],
			       sizeof(scaling->scaling_list_8x8[0]));

	cedrus_h264_write_sram(dev, CEDRUS_SRAM_H264_SCALING_LIST_8x8_1,
			       scaling->scaling_list_8x8[3],
			       sizeof(scaling->scaling_list_8x8[3]));

	cedrus_h264_write_sram(dev, CEDRUS_SRAM_H264_SCALING_LIST_4x4,
			       scaling->scaling_list_4x4,
			       sizeof(scaling->scaling_list_4x4));
}