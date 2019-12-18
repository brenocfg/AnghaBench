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
struct v4l2_ctrl_h264_slice_params {scalar_t__ num_ref_idx_l0_active_minus1; int /*<<< orphan*/  ref_pic_list0; } ;
struct TYPE_2__ {struct v4l2_ctrl_h264_slice_params* slice_params; } ;
struct cedrus_run {TYPE_1__ h264; } ;
struct cedrus_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEDRUS_SRAM_H264_REF_LIST_0 ; 
 int /*<<< orphan*/  _cedrus_write_ref_list (struct cedrus_ctx*,struct cedrus_run*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cedrus_write_ref_list0(struct cedrus_ctx *ctx,
				   struct cedrus_run *run)
{
	const struct v4l2_ctrl_h264_slice_params *slice = run->h264.slice_params;

	_cedrus_write_ref_list(ctx, run,
			       slice->ref_pic_list0,
			       slice->num_ref_idx_l0_active_minus1 + 1,
			       CEDRUS_SRAM_H264_REF_LIST_0);
}