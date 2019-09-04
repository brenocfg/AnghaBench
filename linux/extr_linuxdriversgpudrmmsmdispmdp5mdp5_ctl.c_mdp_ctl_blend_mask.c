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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum mdp_mixer_stage_id { ____Placeholder_mdp_mixer_stage_id } mdp_mixer_stage_id ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_DMA0 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_DMA1 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_RGB0 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_RGB1 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_RGB2 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_RGB3 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_VIG0 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_VIG1 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_VIG2 (int) ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_VIG3 (int) ; 
#define  SSPP_CURSOR0 139 
#define  SSPP_CURSOR1 138 
#define  SSPP_DMA0 137 
#define  SSPP_DMA1 136 
#define  SSPP_RGB0 135 
#define  SSPP_RGB1 134 
#define  SSPP_RGB2 133 
#define  SSPP_RGB3 132 
#define  SSPP_VIG0 131 
#define  SSPP_VIG1 130 
#define  SSPP_VIG2 129 
#define  SSPP_VIG3 128 

__attribute__((used)) static u32 mdp_ctl_blend_mask(enum mdp5_pipe pipe,
		enum mdp_mixer_stage_id stage)
{
	switch (pipe) {
	case SSPP_VIG0: return MDP5_CTL_LAYER_REG_VIG0(stage);
	case SSPP_VIG1: return MDP5_CTL_LAYER_REG_VIG1(stage);
	case SSPP_VIG2: return MDP5_CTL_LAYER_REG_VIG2(stage);
	case SSPP_RGB0: return MDP5_CTL_LAYER_REG_RGB0(stage);
	case SSPP_RGB1: return MDP5_CTL_LAYER_REG_RGB1(stage);
	case SSPP_RGB2: return MDP5_CTL_LAYER_REG_RGB2(stage);
	case SSPP_DMA0: return MDP5_CTL_LAYER_REG_DMA0(stage);
	case SSPP_DMA1: return MDP5_CTL_LAYER_REG_DMA1(stage);
	case SSPP_VIG3: return MDP5_CTL_LAYER_REG_VIG3(stage);
	case SSPP_RGB3: return MDP5_CTL_LAYER_REG_RGB3(stage);
	case SSPP_CURSOR0:
	case SSPP_CURSOR1:
	default:	return 0;
	}
}