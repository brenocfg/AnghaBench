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
struct split_pipe_cfg {int en; scalar_t__ mode; scalar_t__ intf; scalar_t__ split_flush_en; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_mdp {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int) ; 
 int FLD_INTF_1_SW_TRG_MUX ; 
 int FLD_INTF_2_SW_TRG_MUX ; 
 int FLD_SPLIT_DISPLAY_CMD ; 
 scalar_t__ INTF_2 ; 
 scalar_t__ INTF_MODE_CMD ; 
 int /*<<< orphan*/  SPLIT_DISPLAY_EN ; 
 int /*<<< orphan*/  SPLIT_DISPLAY_LOWER_PIPE_CTRL ; 
 int /*<<< orphan*/  SPLIT_DISPLAY_UPPER_PIPE_CTRL ; 
 int /*<<< orphan*/  SSPP_SPARE ; 

__attribute__((used)) static void dpu_hw_setup_split_pipe(struct dpu_hw_mdp *mdp,
		struct split_pipe_cfg *cfg)
{
	struct dpu_hw_blk_reg_map *c;
	u32 upper_pipe = 0;
	u32 lower_pipe = 0;

	if (!mdp || !cfg)
		return;

	c = &mdp->hw;

	if (cfg->en) {
		if (cfg->mode == INTF_MODE_CMD) {
			lower_pipe = FLD_SPLIT_DISPLAY_CMD;
			/* interface controlling sw trigger */
			if (cfg->intf == INTF_2)
				lower_pipe |= FLD_INTF_1_SW_TRG_MUX;
			else
				lower_pipe |= FLD_INTF_2_SW_TRG_MUX;
			upper_pipe = lower_pipe;
		} else {
			if (cfg->intf == INTF_2) {
				lower_pipe = FLD_INTF_1_SW_TRG_MUX;
				upper_pipe = FLD_INTF_2_SW_TRG_MUX;
			} else {
				lower_pipe = FLD_INTF_2_SW_TRG_MUX;
				upper_pipe = FLD_INTF_1_SW_TRG_MUX;
			}
		}
	}

	DPU_REG_WRITE(c, SSPP_SPARE, cfg->split_flush_en ? 0x1 : 0x0);
	DPU_REG_WRITE(c, SPLIT_DISPLAY_LOWER_PIPE_CTRL, lower_pipe);
	DPU_REG_WRITE(c, SPLIT_DISPLAY_UPPER_PIPE_CTRL, upper_pipe);
	DPU_REG_WRITE(c, SPLIT_DISPLAY_EN, cfg->en & 0x1);
}