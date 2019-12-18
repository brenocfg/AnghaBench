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
struct vop_win {int dummy; } ;
struct vop {int /*<<< orphan*/  reg_lock; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vop* to_vop (int /*<<< orphan*/ ) ; 
 struct vop_win* to_vop_win (struct drm_plane*) ; 
 int /*<<< orphan*/  vop_win_disable (struct vop*,struct vop_win*) ; 

__attribute__((used)) static void vop_plane_atomic_disable(struct drm_plane *plane,
				     struct drm_plane_state *old_state)
{
	struct vop_win *vop_win = to_vop_win(plane);
	struct vop *vop = to_vop(old_state->crtc);

	if (!old_state->crtc)
		return;

	spin_lock(&vop->reg_lock);

	vop_win_disable(vop, vop_win);

	spin_unlock(&vop->reg_lock);
}