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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct dpu_hw_pipe {int /*<<< orphan*/  hw; TYPE_1__* cap; } ;
struct TYPE_2__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 scalar_t__ DPU_REG_READ (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPU_SSPP_CSC ; 
 int /*<<< orphan*/  DPU_SSPP_SCALER_QSEED2 ; 
 scalar_t__ SSPP_VIG_OP_MODE ; 
 scalar_t__ _sspp_subblk_offset (struct dpu_hw_pipe*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _sspp_setup_opmode(struct dpu_hw_pipe *ctx,
		u32 mask, u8 en)
{
	u32 idx;
	u32 opmode;

	if (!test_bit(DPU_SSPP_SCALER_QSEED2, &ctx->cap->features) ||
		_sspp_subblk_offset(ctx, DPU_SSPP_SCALER_QSEED2, &idx) ||
		!test_bit(DPU_SSPP_CSC, &ctx->cap->features))
		return;

	opmode = DPU_REG_READ(&ctx->hw, SSPP_VIG_OP_MODE + idx);

	if (en)
		opmode |= mask;
	else
		opmode &= ~mask;

	DPU_REG_WRITE(&ctx->hw, SSPP_VIG_OP_MODE + idx, opmode);
}