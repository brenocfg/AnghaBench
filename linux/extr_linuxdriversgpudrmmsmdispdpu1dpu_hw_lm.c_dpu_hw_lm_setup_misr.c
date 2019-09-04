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
typedef  int u32 ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_mixer {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int) ; 
 int INTF_MISR_CTRL_FREE_RUN_MASK ; 
 int /*<<< orphan*/  LM_MISR_CTRL ; 
 int MISR_CTRL_ENABLE ; 
 int MISR_CTRL_STATUS_CLEAR ; 
 int MISR_FRAME_COUNT_MASK ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dpu_hw_lm_setup_misr(struct dpu_hw_mixer *ctx,
				bool enable, u32 frame_count)
{
	struct dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 config = 0;

	DPU_REG_WRITE(c, LM_MISR_CTRL, MISR_CTRL_STATUS_CLEAR);
	/* clear misr data */
	wmb();

	if (enable)
		config = (frame_count & MISR_FRAME_COUNT_MASK) |
			MISR_CTRL_ENABLE | INTF_MISR_CTRL_FREE_RUN_MASK;

	DPU_REG_WRITE(c, LM_MISR_CTRL, config);
}