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
struct TYPE_5__ {int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct intel_plane {int id; TYPE_2__ base; } ;
struct TYPE_7__ {struct g4x_pipe_wm* raw; } ;
struct TYPE_8__ {TYPE_3__ vlv; } ;
struct intel_crtc_state {TYPE_4__ wm; } ;
struct g4x_pipe_wm {int* plane; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int PLANE_CURSOR ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 size_t VLV_WM_LEVEL_DDR_DVFS ; 
 size_t VLV_WM_LEVEL_PM2 ; 
 size_t VLV_WM_LEVEL_PM5 ; 
 int intel_wm_num_levels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_wm_plane_visible (struct intel_crtc_state*,struct intel_plane_state const*) ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 
 int vlv_compute_wm_level (struct intel_crtc_state*,struct intel_plane_state const*,int) ; 
 int vlv_raw_plane_wm_set (struct intel_crtc_state*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vlv_raw_plane_wm_compute(struct intel_crtc_state *crtc_state,
				     const struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	enum plane_id plane_id = plane->id;
	int num_levels = intel_wm_num_levels(to_i915(plane->base.dev));
	int level;
	bool dirty = false;

	if (!intel_wm_plane_visible(crtc_state, plane_state)) {
		dirty |= vlv_raw_plane_wm_set(crtc_state, 0, plane_id, 0);
		goto out;
	}

	for (level = 0; level < num_levels; level++) {
		struct g4x_pipe_wm *raw = &crtc_state->wm.vlv.raw[level];
		int wm = vlv_compute_wm_level(crtc_state, plane_state, level);
		int max_wm = plane_id == PLANE_CURSOR ? 63 : 511;

		if (wm > max_wm)
			break;

		dirty |= raw->plane[plane_id] != wm;
		raw->plane[plane_id] = wm;
	}

	/* mark all higher levels as invalid */
	dirty |= vlv_raw_plane_wm_set(crtc_state, level, plane_id, USHRT_MAX);

out:
	if (dirty)
		DRM_DEBUG_KMS("%s watermarks: PM2=%d, PM5=%d, DDR DVFS=%d\n",
			      plane->base.name,
			      crtc_state->wm.vlv.raw[VLV_WM_LEVEL_PM2].plane[plane_id],
			      crtc_state->wm.vlv.raw[VLV_WM_LEVEL_PM5].plane[plane_id],
			      crtc_state->wm.vlv.raw[VLV_WM_LEVEL_DDR_DVFS].plane[plane_id]);

	return dirty;
}