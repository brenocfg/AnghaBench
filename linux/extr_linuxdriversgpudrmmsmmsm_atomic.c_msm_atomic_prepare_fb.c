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
struct msm_kms {int /*<<< orphan*/  aspace; } ;
struct msm_gem_object {int /*<<< orphan*/  resv; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct drm_gem_object {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_set_fence_for_plane (struct drm_plane_state*,struct dma_fence*) ; 
 struct drm_gem_object* msm_framebuffer_bo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msm_framebuffer_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_fence* reservation_object_get_excl_rcu (int /*<<< orphan*/ ) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

int msm_atomic_prepare_fb(struct drm_plane *plane,
			  struct drm_plane_state *new_state)
{
	struct msm_drm_private *priv = plane->dev->dev_private;
	struct msm_kms *kms = priv->kms;
	struct drm_gem_object *obj;
	struct msm_gem_object *msm_obj;
	struct dma_fence *fence;

	if (!new_state->fb)
		return 0;

	obj = msm_framebuffer_bo(new_state->fb, 0);
	msm_obj = to_msm_bo(obj);
	fence = reservation_object_get_excl_rcu(msm_obj->resv);

	drm_atomic_set_fence_for_plane(new_state, fence);

	return msm_framebuffer_prepare(new_state->fb, kms->aspace);
}