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
typedef  int /*<<< orphan*/  uint32_t ;
struct dpu_hw_pixel_ext {int dummy; } ;
struct dpu_plane_state {int /*<<< orphan*/  scaler3_cfg; struct dpu_hw_pixel_ext pixel_ext; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; } ;
struct dpu_plane {TYPE_2__ pipe_cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixel_format; } ;
struct dpu_format {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,int,int,int) ; 
 int /*<<< orphan*/  _dpu_plane_setup_scaler3 (struct dpu_plane*,struct dpu_plane_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dpu_format const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_format_horz_chroma_subsampling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_format_vert_chroma_subsampling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_rect_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_rect_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _dpu_plane_setup_scaler(struct dpu_plane *pdpu,
		struct dpu_plane_state *pstate,
		const struct dpu_format *fmt, bool color_fill)
{
	struct dpu_hw_pixel_ext *pe;
	uint32_t chroma_subsmpl_h, chroma_subsmpl_v;

	if (!pdpu || !fmt || !pstate) {
		DPU_ERROR("invalid arg(s), plane %d fmt %d state %d\n",
				pdpu != 0, fmt != 0, pstate != 0);
		return;
	}

	pe = &pstate->pixel_ext;

	/* don't chroma subsample if decimating */
	chroma_subsmpl_h =
		drm_format_horz_chroma_subsampling(fmt->base.pixel_format);
	chroma_subsmpl_v =
		drm_format_vert_chroma_subsampling(fmt->base.pixel_format);

	/* update scaler. calculate default config for QSEED3 */
	_dpu_plane_setup_scaler3(pdpu, pstate,
			drm_rect_width(&pdpu->pipe_cfg.src_rect),
			drm_rect_height(&pdpu->pipe_cfg.src_rect),
			drm_rect_width(&pdpu->pipe_cfg.dst_rect),
			drm_rect_height(&pdpu->pipe_cfg.dst_rect),
			&pstate->scaler3_cfg, fmt,
			chroma_subsmpl_h, chroma_subsmpl_v);
}