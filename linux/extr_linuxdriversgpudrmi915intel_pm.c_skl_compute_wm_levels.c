#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct skl_wm_params {int dummy; } ;
struct skl_wm_level {int dummy; } ;
struct skl_plane_wm {int is_planar; struct skl_wm_level* wm; struct skl_wm_level* uv_wm; } ;
struct skl_ddb_allocation {int /*<<< orphan*/ ** plane; int /*<<< orphan*/ ** uv_plane; } ;
struct TYPE_8__ {TYPE_3__* fb; struct drm_plane* plane; } ;
struct intel_plane_state {TYPE_4__ base; } ;
struct intel_plane {int id; } ;
struct TYPE_5__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_crtc {int pipe; } ;
struct drm_plane {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_7__ {TYPE_2__* format; } ;
struct TYPE_6__ {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_NV12 ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int ilk_wm_max_level (struct drm_i915_private const*) ; 
 int skl_compute_plane_wm (struct drm_i915_private const*,struct intel_crtc_state*,struct intel_plane_state const*,int /*<<< orphan*/ ,int,struct skl_wm_params const*,struct skl_wm_level*,struct skl_wm_level*) ; 
 int /*<<< orphan*/  skl_ddb_entry_size (int /*<<< orphan*/ *) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static int
skl_compute_wm_levels(const struct drm_i915_private *dev_priv,
		      struct skl_ddb_allocation *ddb,
		      struct intel_crtc_state *cstate,
		      const struct intel_plane_state *intel_pstate,
		      const struct skl_wm_params *wm_params,
		      struct skl_plane_wm *wm,
		      int plane_id)
{
	struct intel_crtc *intel_crtc = to_intel_crtc(cstate->base.crtc);
	struct drm_plane *plane = intel_pstate->base.plane;
	struct intel_plane *intel_plane = to_intel_plane(plane);
	uint16_t ddb_blocks;
	enum pipe pipe = intel_crtc->pipe;
	int level, max_level = ilk_wm_max_level(dev_priv);
	enum plane_id intel_plane_id = intel_plane->id;
	int ret;

	if (WARN_ON(!intel_pstate->base.fb))
		return -EINVAL;

	ddb_blocks = plane_id ?
		     skl_ddb_entry_size(&ddb->uv_plane[pipe][intel_plane_id]) :
		     skl_ddb_entry_size(&ddb->plane[pipe][intel_plane_id]);

	for (level = 0; level <= max_level; level++) {
		struct skl_wm_level *result = plane_id ? &wm->uv_wm[level] :
							  &wm->wm[level];
		struct skl_wm_level *result_prev;

		if (level)
			result_prev = plane_id ? &wm->uv_wm[level - 1] :
						  &wm->wm[level - 1];
		else
			result_prev = plane_id ? &wm->uv_wm[0] : &wm->wm[0];

		ret = skl_compute_plane_wm(dev_priv,
					   cstate,
					   intel_pstate,
					   ddb_blocks,
					   level,
					   wm_params,
					   result_prev,
					   result);
		if (ret)
			return ret;
	}

	if (intel_pstate->base.fb->format->format == DRM_FORMAT_NV12)
		wm->is_planar = true;

	return 0;
}