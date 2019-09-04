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
typedef  scalar_t__ u32 ;
struct dpu_hw_pipe_qos_cfg {int creq_lut; } ;
struct dpu_hw_pipe {int /*<<< orphan*/  hw; TYPE_1__* cap; } ;
struct TYPE_2__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  DPU_SSPP_QOS_8LVL ; 
 int /*<<< orphan*/  DPU_SSPP_SRC ; 
 scalar_t__ SSPP_CREQ_LUT ; 
 scalar_t__ SSPP_CREQ_LUT_0 ; 
 scalar_t__ SSPP_CREQ_LUT_1 ; 
 scalar_t__ _sspp_subblk_offset (struct dpu_hw_pipe*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpu_hw_sspp_setup_creq_lut(struct dpu_hw_pipe *ctx,
		struct dpu_hw_pipe_qos_cfg *cfg)
{
	u32 idx;

	if (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		return;

	if (ctx->cap && test_bit(DPU_SSPP_QOS_8LVL, &ctx->cap->features)) {
		DPU_REG_WRITE(&ctx->hw, SSPP_CREQ_LUT_0 + idx, cfg->creq_lut);
		DPU_REG_WRITE(&ctx->hw, SSPP_CREQ_LUT_1 + idx,
				cfg->creq_lut >> 32);
	} else {
		DPU_REG_WRITE(&ctx->hw, SSPP_CREQ_LUT + idx, cfg->creq_lut);
	}
}