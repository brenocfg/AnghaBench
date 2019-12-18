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
struct drm_crtc_state {int plane_mask; int enable; int /*<<< orphan*/  state; } ;
struct drm_crtc {int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 int EINVAL ; 
 int drm_atomic_add_affected_planes (int /*<<< orphan*/ ,struct drm_crtc*) ; 
 int drm_plane_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_simple_kms_crtc_check(struct drm_crtc *crtc,
				     struct drm_crtc_state *state)
{
	bool has_primary = state->plane_mask &
			   drm_plane_mask(crtc->primary);

	/* We always want to have an active plane with an active CRTC */
	if (has_primary != state->enable)
		return -EINVAL;

	return drm_atomic_add_affected_planes(state->state, crtc);
}