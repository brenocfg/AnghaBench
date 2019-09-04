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
struct rcar_du_vsp_plane {int /*<<< orphan*/  index; TYPE_2__* vsp; } ;
struct rcar_du_crtc {int /*<<< orphan*/  vsp_pipe; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsp; } ;
struct TYPE_3__ {scalar_t__ visible; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcar_du_vsp_plane_setup (struct rcar_du_vsp_plane*) ; 
 struct rcar_du_crtc* to_rcar_crtc (int /*<<< orphan*/ ) ; 
 struct rcar_du_vsp_plane* to_rcar_vsp_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  vsp1_du_atomic_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_du_vsp_plane_atomic_update(struct drm_plane *plane,
					struct drm_plane_state *old_state)
{
	struct rcar_du_vsp_plane *rplane = to_rcar_vsp_plane(plane);
	struct rcar_du_crtc *crtc = to_rcar_crtc(old_state->crtc);

	if (plane->state->visible)
		rcar_du_vsp_plane_setup(rplane);
	else
		vsp1_du_atomic_update(rplane->vsp->vsp, crtc->vsp_pipe,
				      rplane->index, NULL);
}