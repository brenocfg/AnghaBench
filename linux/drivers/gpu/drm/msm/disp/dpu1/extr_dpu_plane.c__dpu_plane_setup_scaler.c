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
struct drm_format_info {int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
struct dpu_plane_state {int /*<<< orphan*/  scaler3_cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; } ;
struct dpu_plane {TYPE_2__ pipe_cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixel_format; } ;
struct dpu_format {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_plane_setup_scaler3 (struct dpu_plane*,struct dpu_plane_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dpu_format const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_rect_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_rect_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _dpu_plane_setup_scaler(struct dpu_plane *pdpu,
		struct dpu_plane_state *pstate,
		const struct dpu_format *fmt, bool color_fill)
{
	const struct drm_format_info *info = drm_format_info(fmt->base.pixel_format);

	/* don't chroma subsample if decimating */
	/* update scaler. calculate default config for QSEED3 */
	_dpu_plane_setup_scaler3(pdpu, pstate,
			drm_rect_width(&pdpu->pipe_cfg.src_rect),
			drm_rect_height(&pdpu->pipe_cfg.src_rect),
			drm_rect_width(&pdpu->pipe_cfg.dst_rect),
			drm_rect_height(&pdpu->pipe_cfg.dst_rect),
			&pstate->scaler3_cfg, fmt,
			info->hsub, info->vsub);
}