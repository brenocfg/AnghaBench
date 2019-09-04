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
typedef  scalar_t__ u32 ;
struct dpu_hw_pipe_qos_cfg {int /*<<< orphan*/  safe_lut; int /*<<< orphan*/  danger_lut; } ;
struct dpu_hw_pipe {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_SSPP_SRC ; 
 scalar_t__ SSPP_DANGER_LUT ; 
 scalar_t__ SSPP_SAFE_LUT ; 
 scalar_t__ _sspp_subblk_offset (struct dpu_hw_pipe*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void dpu_hw_sspp_setup_danger_safe_lut(struct dpu_hw_pipe *ctx,
		struct dpu_hw_pipe_qos_cfg *cfg)
{
	u32 idx;

	if (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		return;

	DPU_REG_WRITE(&ctx->hw, SSPP_DANGER_LUT + idx, cfg->danger_lut);
	DPU_REG_WRITE(&ctx->hw, SSPP_SAFE_LUT + idx, cfg->safe_lut);
}