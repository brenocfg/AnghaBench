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
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_ctl {int mixer_count; struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_LAYER (scalar_t__) ; 
 int /*<<< orphan*/  CTL_LAYER_EXT (scalar_t__) ; 
 int /*<<< orphan*/  CTL_LAYER_EXT2 (scalar_t__) ; 
 int /*<<< orphan*/  CTL_LAYER_EXT3 (scalar_t__) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LM_0 ; 

__attribute__((used)) static void dpu_hw_ctl_clear_all_blendstages(struct dpu_hw_ctl *ctx)
{
	struct dpu_hw_blk_reg_map *c = &ctx->hw;
	int i;

	for (i = 0; i < ctx->mixer_count; i++) {
		DPU_REG_WRITE(c, CTL_LAYER(LM_0 + i), 0);
		DPU_REG_WRITE(c, CTL_LAYER_EXT(LM_0 + i), 0);
		DPU_REG_WRITE(c, CTL_LAYER_EXT2(LM_0 + i), 0);
		DPU_REG_WRITE(c, CTL_LAYER_EXT3(LM_0 + i), 0);
	}
}