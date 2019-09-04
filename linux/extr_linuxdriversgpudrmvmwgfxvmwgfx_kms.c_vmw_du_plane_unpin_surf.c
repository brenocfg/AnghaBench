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
struct vmw_plane_state {TYPE_1__* surf; scalar_t__ pinned; } ;
struct TYPE_2__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  vmw_resource_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_surface_unreference (TYPE_1__**) ; 

void vmw_du_plane_unpin_surf(struct vmw_plane_state *vps,
			     bool unreference)
{
	if (vps->surf) {
		if (vps->pinned) {
			vmw_resource_unpin(&vps->surf->res);
			vps->pinned--;
		}

		if (unreference) {
			if (vps->pinned)
				DRM_ERROR("Surface still pinned\n");
			vmw_surface_unreference(&vps->surf);
		}
	}
}