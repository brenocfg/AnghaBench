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
struct msm_gem_object {int /*<<< orphan*/  resv; } ;
struct msm_gem_address_space {int dummy; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {TYPE_1__ base; } ;
struct dpu_plane_state {struct msm_gem_address_space* aspace; } ;
struct dpu_plane {int dummy; } ;
struct dpu_hw_fmt_layout {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PLANE (struct dpu_plane*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_ERROR_PLANE (struct dpu_plane*,char*,...) ; 
 int _dpu_plane_get_aspace (struct dpu_plane*,struct dpu_plane_state*,struct msm_gem_address_space**) ; 
 int dpu_format_populate_layout (struct msm_gem_address_space*,struct drm_framebuffer*,struct dpu_hw_fmt_layout*) ; 
 int /*<<< orphan*/  drm_atomic_set_fence_for_plane (struct drm_plane_state*,struct dma_fence*) ; 
 struct drm_gem_object* msm_framebuffer_bo (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int msm_framebuffer_prepare (struct drm_framebuffer*,struct msm_gem_address_space*) ; 
 struct dma_fence* reservation_object_get_excl_rcu (int /*<<< orphan*/ ) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 
 struct dpu_plane_state* to_dpu_plane_state (struct drm_plane_state*) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int dpu_plane_prepare_fb(struct drm_plane *plane,
		struct drm_plane_state *new_state)
{
	struct drm_framebuffer *fb = new_state->fb;
	struct dpu_plane *pdpu = to_dpu_plane(plane);
	struct dpu_plane_state *pstate = to_dpu_plane_state(new_state);
	struct dpu_hw_fmt_layout layout;
	struct drm_gem_object *obj;
	struct msm_gem_object *msm_obj;
	struct dma_fence *fence;
	struct msm_gem_address_space *aspace;
	int ret;

	if (!new_state->fb)
		return 0;

	DPU_DEBUG_PLANE(pdpu, "FB[%u]\n", fb->base.id);

	ret = _dpu_plane_get_aspace(pdpu, pstate, &aspace);
	if (ret) {
		DPU_ERROR_PLANE(pdpu, "Failed to get aspace\n");
		return ret;
	}

	/* cache aspace */
	pstate->aspace = aspace;

	/*
	 * TODO: Need to sort out the msm_framebuffer_prepare() call below so
	 *       we can use msm_atomic_prepare_fb() instead of doing the
	 *       implicit fence and fb prepare by hand here.
	 */
	obj = msm_framebuffer_bo(new_state->fb, 0);
	msm_obj = to_msm_bo(obj);
	fence = reservation_object_get_excl_rcu(msm_obj->resv);
	if (fence)
		drm_atomic_set_fence_for_plane(new_state, fence);

	if (pstate->aspace) {
		ret = msm_framebuffer_prepare(new_state->fb,
				pstate->aspace);
		if (ret) {
			DPU_ERROR("failed to prepare framebuffer\n");
			return ret;
		}
	}

	/* validate framebuffer layout before commit */
	ret = dpu_format_populate_layout(pstate->aspace,
			new_state->fb, &layout);
	if (ret) {
		DPU_ERROR_PLANE(pdpu, "failed to get format layout, %d\n", ret);
		return ret;
	}

	return 0;
}