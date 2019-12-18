#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct drm_format_name_buf {int dummy; } ;
struct dpu_plane_state {int /*<<< orphan*/  stage; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* setup_blend_config ) (struct dpu_hw_mixer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;
struct dpu_hw_mixer {TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixel_format; } ;
struct dpu_format {int /*<<< orphan*/  alpha_enable; TYPE_1__ base; } ;
struct dpu_crtc_mixer {struct dpu_hw_mixer* hw_lm; } ;

/* Variables and functions */
 int DPU_BLEND_BG_ALPHA_BG_CONST ; 
 int DPU_BLEND_BG_ALPHA_FG_PIXEL ; 
 int DPU_BLEND_BG_INV_ALPHA ; 
 int DPU_BLEND_FG_ALPHA_FG_CONST ; 
 int DPU_BLEND_FG_ALPHA_FG_PIXEL ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_get_format_name (int /*<<< orphan*/ ,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_mixer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _dpu_crtc_setup_blend_cfg(struct dpu_crtc_mixer *mixer,
		struct dpu_plane_state *pstate, struct dpu_format *format)
{
	struct dpu_hw_mixer *lm = mixer->hw_lm;
	uint32_t blend_op;
	struct drm_format_name_buf format_name;

	/* default to opaque blending */
	blend_op = DPU_BLEND_FG_ALPHA_FG_CONST |
		DPU_BLEND_BG_ALPHA_BG_CONST;

	if (format->alpha_enable) {
		/* coverage blending */
		blend_op = DPU_BLEND_FG_ALPHA_FG_PIXEL |
			DPU_BLEND_BG_ALPHA_FG_PIXEL |
			DPU_BLEND_BG_INV_ALPHA;
	}

	lm->ops.setup_blend_config(lm, pstate->stage,
				0xFF, 0, blend_op);

	DPU_DEBUG("format:%s, alpha_en:%u blend_op:0x%x\n",
		drm_get_format_name(format->base.pixel_format, &format_name),
		format->alpha_enable, blend_op);
}