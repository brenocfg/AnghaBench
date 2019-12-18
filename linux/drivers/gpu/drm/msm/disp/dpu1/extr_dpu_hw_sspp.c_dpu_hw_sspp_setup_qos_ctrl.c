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
struct dpu_hw_pipe_qos_cfg {int creq_vblank; int danger_vblank; scalar_t__ danger_safe_en; scalar_t__ vblank_en; } ;
struct dpu_hw_pipe {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  DPU_SSPP_SRC ; 
 int SSPP_QOS_CTRL ; 
 int SSPP_QOS_CTRL_CREQ_VBLANK_MASK ; 
 int SSPP_QOS_CTRL_CREQ_VBLANK_OFF ; 
 int SSPP_QOS_CTRL_DANGER_SAFE_EN ; 
 int SSPP_QOS_CTRL_DANGER_VBLANK_MASK ; 
 int SSPP_QOS_CTRL_DANGER_VBLANK_OFF ; 
 int SSPP_QOS_CTRL_VBLANK_EN ; 
 scalar_t__ _sspp_subblk_offset (struct dpu_hw_pipe*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void dpu_hw_sspp_setup_qos_ctrl(struct dpu_hw_pipe *ctx,
		struct dpu_hw_pipe_qos_cfg *cfg)
{
	u32 idx;
	u32 qos_ctrl = 0;

	if (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		return;

	if (cfg->vblank_en) {
		qos_ctrl |= ((cfg->creq_vblank &
				SSPP_QOS_CTRL_CREQ_VBLANK_MASK) <<
				SSPP_QOS_CTRL_CREQ_VBLANK_OFF);
		qos_ctrl |= ((cfg->danger_vblank &
				SSPP_QOS_CTRL_DANGER_VBLANK_MASK) <<
				SSPP_QOS_CTRL_DANGER_VBLANK_OFF);
		qos_ctrl |= SSPP_QOS_CTRL_VBLANK_EN;
	}

	if (cfg->danger_safe_en)
		qos_ctrl |= SSPP_QOS_CTRL_DANGER_SAFE_EN;

	DPU_REG_WRITE(&ctx->hw, SSPP_QOS_CTRL + idx, qos_ctrl);
}