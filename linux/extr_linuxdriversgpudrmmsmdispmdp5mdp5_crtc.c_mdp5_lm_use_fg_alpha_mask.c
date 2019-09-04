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

/* Variables and functions */
 int /*<<< orphan*/  MDP5_LM_BLEND_COLOR_OUT_STAGE0_FG_ALPHA ; 
 int /*<<< orphan*/  MDP5_LM_BLEND_COLOR_OUT_STAGE1_FG_ALPHA ; 
 int /*<<< orphan*/  MDP5_LM_BLEND_COLOR_OUT_STAGE2_FG_ALPHA ; 
 int /*<<< orphan*/  MDP5_LM_BLEND_COLOR_OUT_STAGE3_FG_ALPHA ; 
 int /*<<< orphan*/  MDP5_LM_BLEND_COLOR_OUT_STAGE4_FG_ALPHA ; 
 int /*<<< orphan*/  MDP5_LM_BLEND_COLOR_OUT_STAGE5_FG_ALPHA ; 
 int /*<<< orphan*/  MDP5_LM_BLEND_COLOR_OUT_STAGE6_FG_ALPHA ; 
#define  STAGE0 134 
#define  STAGE1 133 
#define  STAGE2 132 
#define  STAGE3 131 
#define  STAGE4 130 
#define  STAGE5 129 
#define  STAGE6 128 

__attribute__((used)) static inline u32 mdp5_lm_use_fg_alpha_mask(enum mdp_mixer_stage_id stage)
{
	switch (stage) {
	case STAGE0: return MDP5_LM_BLEND_COLOR_OUT_STAGE0_FG_ALPHA;
	case STAGE1: return MDP5_LM_BLEND_COLOR_OUT_STAGE1_FG_ALPHA;
	case STAGE2: return MDP5_LM_BLEND_COLOR_OUT_STAGE2_FG_ALPHA;
	case STAGE3: return MDP5_LM_BLEND_COLOR_OUT_STAGE3_FG_ALPHA;
	case STAGE4: return MDP5_LM_BLEND_COLOR_OUT_STAGE4_FG_ALPHA;
	case STAGE5: return MDP5_LM_BLEND_COLOR_OUT_STAGE5_FG_ALPHA;
	case STAGE6: return MDP5_LM_BLEND_COLOR_OUT_STAGE6_FG_ALPHA;
	default:
		return 0;
	}
}