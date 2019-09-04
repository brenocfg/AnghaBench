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
struct vmw_plane_state {scalar_t__ bo_size; scalar_t__ bo; } ;
struct drm_plane_state {struct drm_crtc* crtc; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_bo_unpin (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (scalar_t__*) ; 
 int /*<<< orphan*/  vmw_du_plane_cleanup_fb (struct drm_plane*,struct drm_plane_state*) ; 
 struct vmw_plane_state* vmw_plane_state_to_vps (struct drm_plane_state*) ; 
 int /*<<< orphan*/  vmw_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmw_sou_primary_plane_cleanup_fb(struct drm_plane *plane,
				 struct drm_plane_state *old_state)
{
	struct vmw_plane_state *vps = vmw_plane_state_to_vps(old_state);
	struct drm_crtc *crtc = plane->state->crtc ?
		plane->state->crtc : old_state->crtc;

	if (vps->bo)
		vmw_bo_unpin(vmw_priv(crtc->dev), vps->bo, false);
	vmw_bo_unreference(&vps->bo);
	vps->bo_size = 0;

	vmw_du_plane_cleanup_fb(plane, old_state);
}