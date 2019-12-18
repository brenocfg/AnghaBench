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
struct vmw_private {int /*<<< orphan*/  cmdbuf_mutex; } ;
struct vmw_framebuffer {int dummy; } ;
struct vmw_fence_obj {int dummy; } ;
struct TYPE_4__ {int cpu_blit; int intr; int /*<<< orphan*/  post_clip; int /*<<< orphan*/  clip; int /*<<< orphan*/  pre_clip; int /*<<< orphan*/  post_prepare; int /*<<< orphan*/  calc_fifo_size; int /*<<< orphan*/ * mutex; struct vmw_fence_obj** out_fence; struct vmw_framebuffer* vfb; int /*<<< orphan*/  du; struct vmw_private* dev_priv; struct drm_plane_state* old_state; struct drm_plane* plane; } ;
struct vmw_du_update_plane_surface {TYPE_2__ base; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vmw_du_update_plane_surface*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmw_crtc_to_du (int /*<<< orphan*/ ) ; 
 int vmw_du_helper_plane_update (TYPE_2__*) ; 
 int /*<<< orphan*/  vmw_sou_surface_clip_rect ; 
 int /*<<< orphan*/  vmw_sou_surface_fifo_size ; 
 int /*<<< orphan*/  vmw_sou_surface_post_clip ; 
 int /*<<< orphan*/  vmw_sou_surface_post_prepare ; 
 int /*<<< orphan*/  vmw_sou_surface_pre_clip ; 

__attribute__((used)) static int vmw_sou_plane_update_surface(struct vmw_private *dev_priv,
					struct drm_plane *plane,
					struct drm_plane_state *old_state,
					struct vmw_framebuffer *vfb,
					struct vmw_fence_obj **out_fence)
{
	struct vmw_du_update_plane_surface srf_update;

	memset(&srf_update, 0, sizeof(struct vmw_du_update_plane_surface));
	srf_update.base.plane = plane;
	srf_update.base.old_state = old_state;
	srf_update.base.dev_priv = dev_priv;
	srf_update.base.du = vmw_crtc_to_du(plane->state->crtc);
	srf_update.base.vfb = vfb;
	srf_update.base.out_fence = out_fence;
	srf_update.base.mutex = &dev_priv->cmdbuf_mutex;
	srf_update.base.cpu_blit = false;
	srf_update.base.intr = true;

	srf_update.base.calc_fifo_size = vmw_sou_surface_fifo_size;
	srf_update.base.post_prepare = vmw_sou_surface_post_prepare;
	srf_update.base.pre_clip = vmw_sou_surface_pre_clip;
	srf_update.base.clip = vmw_sou_surface_clip_rect;
	srf_update.base.post_clip = vmw_sou_surface_post_clip;

	return vmw_du_helper_plane_update(&srf_update.base);
}