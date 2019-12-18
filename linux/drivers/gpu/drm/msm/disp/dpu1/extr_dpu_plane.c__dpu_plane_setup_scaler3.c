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
typedef  size_t uint32_t ;
struct dpu_hw_scaler3_cfg {size_t* phase_step_x; size_t* phase_step_y; size_t* src_width; size_t* src_height; size_t* num_ext_pxls_top; size_t* num_ext_pxls_left; size_t dst_width; size_t dst_height; int blend_cfg; int enable; scalar_t__ lut_flag; int /*<<< orphan*/  alpha_filter_cfg; void* uv_filter_cfg; void* y_rgb_filter_cfg; int /*<<< orphan*/ * preload_y; int /*<<< orphan*/ * preload_x; } ;
struct dpu_plane_state {struct dpu_hw_scaler3_cfg pixel_ext; } ;
struct dpu_plane {int dummy; } ;
struct dpu_hw_pixel_ext {int dummy; } ;
struct dpu_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_FORMAT_IS_YUV (struct dpu_format const*) ; 
 size_t DPU_MAX_PLANES ; 
 int /*<<< orphan*/  DPU_QSEED3_DEFAULT_PRELOAD_H ; 
 int /*<<< orphan*/  DPU_QSEED3_DEFAULT_PRELOAD_V ; 
 int /*<<< orphan*/  DPU_SCALE_ALPHA_BIL ; 
 void* DPU_SCALE_BIL ; 
 size_t DPU_SSPP_COMP_0 ; 
 size_t DPU_SSPP_COMP_1_2 ; 
 size_t DPU_SSPP_COMP_2 ; 
 size_t DPU_SSPP_COMP_3 ; 
 int PHASE_STEP_SHIFT ; 
 int /*<<< orphan*/  memset (struct dpu_hw_scaler3_cfg*,int /*<<< orphan*/ ,int) ; 
 void* mult_frac (int,size_t,size_t) ; 

__attribute__((used)) static void _dpu_plane_setup_scaler3(struct dpu_plane *pdpu,
		struct dpu_plane_state *pstate,
		uint32_t src_w, uint32_t src_h, uint32_t dst_w, uint32_t dst_h,
		struct dpu_hw_scaler3_cfg *scale_cfg,
		const struct dpu_format *fmt,
		uint32_t chroma_subsmpl_h, uint32_t chroma_subsmpl_v)
{
	uint32_t i;

	memset(scale_cfg, 0, sizeof(*scale_cfg));
	memset(&pstate->pixel_ext, 0, sizeof(struct dpu_hw_pixel_ext));

	scale_cfg->phase_step_x[DPU_SSPP_COMP_0] =
		mult_frac((1 << PHASE_STEP_SHIFT), src_w, dst_w);
	scale_cfg->phase_step_y[DPU_SSPP_COMP_0] =
		mult_frac((1 << PHASE_STEP_SHIFT), src_h, dst_h);


	scale_cfg->phase_step_y[DPU_SSPP_COMP_1_2] =
		scale_cfg->phase_step_y[DPU_SSPP_COMP_0] / chroma_subsmpl_v;
	scale_cfg->phase_step_x[DPU_SSPP_COMP_1_2] =
		scale_cfg->phase_step_x[DPU_SSPP_COMP_0] / chroma_subsmpl_h;

	scale_cfg->phase_step_x[DPU_SSPP_COMP_2] =
		scale_cfg->phase_step_x[DPU_SSPP_COMP_1_2];
	scale_cfg->phase_step_y[DPU_SSPP_COMP_2] =
		scale_cfg->phase_step_y[DPU_SSPP_COMP_1_2];

	scale_cfg->phase_step_x[DPU_SSPP_COMP_3] =
		scale_cfg->phase_step_x[DPU_SSPP_COMP_0];
	scale_cfg->phase_step_y[DPU_SSPP_COMP_3] =
		scale_cfg->phase_step_y[DPU_SSPP_COMP_0];

	for (i = 0; i < DPU_MAX_PLANES; i++) {
		scale_cfg->src_width[i] = src_w;
		scale_cfg->src_height[i] = src_h;
		if (i == DPU_SSPP_COMP_1_2 || i == DPU_SSPP_COMP_2) {
			scale_cfg->src_width[i] /= chroma_subsmpl_h;
			scale_cfg->src_height[i] /= chroma_subsmpl_v;
		}
		scale_cfg->preload_x[i] = DPU_QSEED3_DEFAULT_PRELOAD_H;
		scale_cfg->preload_y[i] = DPU_QSEED3_DEFAULT_PRELOAD_V;
		pstate->pixel_ext.num_ext_pxls_top[i] =
			scale_cfg->src_height[i];
		pstate->pixel_ext.num_ext_pxls_left[i] =
			scale_cfg->src_width[i];
	}
	if (!(DPU_FORMAT_IS_YUV(fmt)) && (src_h == dst_h)
		&& (src_w == dst_w))
		return;

	scale_cfg->dst_width = dst_w;
	scale_cfg->dst_height = dst_h;
	scale_cfg->y_rgb_filter_cfg = DPU_SCALE_BIL;
	scale_cfg->uv_filter_cfg = DPU_SCALE_BIL;
	scale_cfg->alpha_filter_cfg = DPU_SCALE_ALPHA_BIL;
	scale_cfg->lut_flag = 0;
	scale_cfg->blend_cfg = 1;
	scale_cfg->enable = 1;
}