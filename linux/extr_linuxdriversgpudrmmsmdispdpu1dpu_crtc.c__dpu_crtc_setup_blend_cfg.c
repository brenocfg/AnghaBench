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
struct dpu_plane_state {int /*<<< orphan*/  stage; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* setup_blend_config ) (struct dpu_hw_mixer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;
struct dpu_hw_mixer {TYPE_1__ ops; } ;
struct dpu_crtc_mixer {struct dpu_hw_mixer* hw_lm; } ;

/* Variables and functions */
 int DPU_BLEND_BG_ALPHA_BG_CONST ; 
 int DPU_BLEND_FG_ALPHA_FG_CONST ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_mixer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _dpu_crtc_setup_blend_cfg(struct dpu_crtc_mixer *mixer,
		struct dpu_plane_state *pstate)
{
	struct dpu_hw_mixer *lm = mixer->hw_lm;

	/* default to opaque blending */
	lm->ops.setup_blend_config(lm, pstate->stage, 0XFF, 0,
				DPU_BLEND_FG_ALPHA_FG_CONST |
				DPU_BLEND_BG_ALPHA_BG_CONST);
}