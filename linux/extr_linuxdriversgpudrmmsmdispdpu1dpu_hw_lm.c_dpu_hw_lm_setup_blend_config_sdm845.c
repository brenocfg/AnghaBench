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
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_mixer {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,scalar_t__,scalar_t__) ; 
 scalar_t__ DPU_STAGE_BASE ; 
 scalar_t__ LM_BLEND0_CONST_ALPHA ; 
 scalar_t__ LM_BLEND0_OP ; 
 scalar_t__ WARN_ON (int) ; 
 int _stage_offset (struct dpu_hw_mixer*,scalar_t__) ; 

__attribute__((used)) static void dpu_hw_lm_setup_blend_config_sdm845(struct dpu_hw_mixer *ctx,
	u32 stage, u32 fg_alpha, u32 bg_alpha, u32 blend_op)
{
	struct dpu_hw_blk_reg_map *c = &ctx->hw;
	int stage_off;
	u32 const_alpha;

	if (stage == DPU_STAGE_BASE)
		return;

	stage_off = _stage_offset(ctx, stage);
	if (WARN_ON(stage_off < 0))
		return;

	const_alpha = (bg_alpha & 0xFF) | ((fg_alpha & 0xFF) << 16);
	DPU_REG_WRITE(c, LM_BLEND0_CONST_ALPHA + stage_off, const_alpha);
	DPU_REG_WRITE(c, LM_BLEND0_OP + stage_off, blend_op);
}