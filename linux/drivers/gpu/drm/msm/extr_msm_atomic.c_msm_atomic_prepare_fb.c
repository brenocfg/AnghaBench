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
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_2__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_fb_prepare_fb (struct drm_plane*,struct drm_plane_state*) ; 
 int msm_framebuffer_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int msm_atomic_prepare_fb(struct drm_plane *plane,
			  struct drm_plane_state *new_state)
{
	struct msm_drm_private *priv = plane->dev->dev_private;
	struct msm_kms *kms = priv->kms;

	if (!new_state->fb)
		return 0;

	drm_gem_fb_prepare_fb(plane, new_state);

	return msm_framebuffer_prepare(new_state->fb, kms->aspace);
}