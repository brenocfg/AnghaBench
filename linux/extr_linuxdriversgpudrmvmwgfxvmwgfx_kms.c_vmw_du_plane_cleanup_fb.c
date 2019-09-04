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
struct vmw_plane_state {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_du_plane_unpin_surf (struct vmw_plane_state*,int) ; 
 struct vmw_plane_state* vmw_plane_state_to_vps (struct drm_plane_state*) ; 

void
vmw_du_plane_cleanup_fb(struct drm_plane *plane,
			struct drm_plane_state *old_state)
{
	struct vmw_plane_state *vps = vmw_plane_state_to_vps(old_state);

	vmw_du_plane_unpin_surf(vps, false);
}