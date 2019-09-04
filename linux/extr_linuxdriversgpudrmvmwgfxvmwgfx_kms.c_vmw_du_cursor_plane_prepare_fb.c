#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vmw_plane_state {scalar_t__ surf; scalar_t__ bo; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_6__ {scalar_t__ bo; } ;
struct TYPE_5__ {scalar_t__ buffer; } ;
struct TYPE_4__ {scalar_t__ surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_bo_reference (scalar_t__) ; 
 int /*<<< orphan*/  vmw_bo_unreference (scalar_t__*) ; 
 TYPE_3__* vmw_framebuffer_to_vfb (struct drm_framebuffer*) ; 
 TYPE_2__* vmw_framebuffer_to_vfbd (struct drm_framebuffer*) ; 
 TYPE_1__* vmw_framebuffer_to_vfbs (struct drm_framebuffer*) ; 
 struct vmw_plane_state* vmw_plane_state_to_vps (struct drm_plane_state*) ; 
 int /*<<< orphan*/  vmw_surface_reference (scalar_t__) ; 
 int /*<<< orphan*/  vmw_surface_unreference (scalar_t__*) ; 

int
vmw_du_cursor_plane_prepare_fb(struct drm_plane *plane,
			       struct drm_plane_state *new_state)
{
	struct drm_framebuffer *fb = new_state->fb;
	struct vmw_plane_state *vps = vmw_plane_state_to_vps(new_state);


	if (vps->surf)
		vmw_surface_unreference(&vps->surf);

	if (vps->bo)
		vmw_bo_unreference(&vps->bo);

	if (fb) {
		if (vmw_framebuffer_to_vfb(fb)->bo) {
			vps->bo = vmw_framebuffer_to_vfbd(fb)->buffer;
			vmw_bo_reference(vps->bo);
		} else {
			vps->surf = vmw_framebuffer_to_vfbs(fb)->surface;
			vmw_surface_reference(vps->surf);
		}
	}

	return 0;
}