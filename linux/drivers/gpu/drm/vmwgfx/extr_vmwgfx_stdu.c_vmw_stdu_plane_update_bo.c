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
struct vmw_private {int capabilities; } ;
struct vmw_framebuffer {int dummy; } ;
struct vmw_fence_obj {int dummy; } ;
struct TYPE_4__ {int cpu_blit; int intr; int /*<<< orphan*/  post_clip; int /*<<< orphan*/  clip; int /*<<< orphan*/  pre_clip; int /*<<< orphan*/  calc_fifo_size; int /*<<< orphan*/ * mutex; struct vmw_fence_obj** out_fence; struct vmw_framebuffer* vfb; int /*<<< orphan*/  du; struct vmw_private* dev_priv; struct drm_plane_state* old_state; struct drm_plane* plane; } ;
struct vmw_du_update_plane_buffer {TYPE_2__ base; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int SVGA_CAP_3D ; 
 int /*<<< orphan*/  memset (struct vmw_du_update_plane_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmw_crtc_to_du (int /*<<< orphan*/ ) ; 
 int vmw_du_helper_plane_update (TYPE_2__*) ; 
 int /*<<< orphan*/  vmw_stdu_bo_clip_cpu ; 
 int /*<<< orphan*/  vmw_stdu_bo_fifo_size ; 
 int /*<<< orphan*/  vmw_stdu_bo_fifo_size_cpu ; 
 int /*<<< orphan*/  vmw_stdu_bo_populate_clip ; 
 int /*<<< orphan*/  vmw_stdu_bo_populate_dma ; 
 int /*<<< orphan*/  vmw_stdu_bo_populate_update ; 
 int /*<<< orphan*/  vmw_stdu_bo_populate_update_cpu ; 
 int /*<<< orphan*/  vmw_stdu_bo_pre_clip_cpu ; 

__attribute__((used)) static int vmw_stdu_plane_update_bo(struct vmw_private *dev_priv,
				    struct drm_plane *plane,
				    struct drm_plane_state *old_state,
				    struct vmw_framebuffer *vfb,
				    struct vmw_fence_obj **out_fence)
{
	struct vmw_du_update_plane_buffer bo_update;

	memset(&bo_update, 0, sizeof(struct vmw_du_update_plane_buffer));
	bo_update.base.plane = plane;
	bo_update.base.old_state = old_state;
	bo_update.base.dev_priv = dev_priv;
	bo_update.base.du = vmw_crtc_to_du(plane->state->crtc);
	bo_update.base.vfb = vfb;
	bo_update.base.out_fence = out_fence;
	bo_update.base.mutex = NULL;
	bo_update.base.cpu_blit = !(dev_priv->capabilities & SVGA_CAP_3D);
	bo_update.base.intr = false;

	/*
	 * VM without 3D support don't have surface DMA command and framebuffer
	 * should be moved out of VRAM.
	 */
	if (bo_update.base.cpu_blit) {
		bo_update.base.calc_fifo_size = vmw_stdu_bo_fifo_size_cpu;
		bo_update.base.pre_clip = vmw_stdu_bo_pre_clip_cpu;
		bo_update.base.clip = vmw_stdu_bo_clip_cpu;
		bo_update.base.post_clip = vmw_stdu_bo_populate_update_cpu;
	} else {
		bo_update.base.calc_fifo_size = vmw_stdu_bo_fifo_size;
		bo_update.base.pre_clip = vmw_stdu_bo_populate_dma;
		bo_update.base.clip = vmw_stdu_bo_populate_clip;
		bo_update.base.post_clip = vmw_stdu_bo_populate_update;
	}

	return vmw_du_helper_plane_update(&bo_update.base);
}