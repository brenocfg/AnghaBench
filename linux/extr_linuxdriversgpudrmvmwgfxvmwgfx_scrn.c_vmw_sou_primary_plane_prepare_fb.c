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
struct vmw_private {int dummy; } ;
struct vmw_plane_state {size_t bo_size; int /*<<< orphan*/ * bo; } ;
struct drm_plane_state {int crtc_w; int crtc_h; struct drm_crtc* crtc; struct drm_framebuffer* fb; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_bo_bo_free ; 
 int vmw_bo_init (struct vmw_private*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int vmw_bo_pin_in_vram (struct vmw_private*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_bo_unreference (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vmw_overlay_pause_all (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_overlay_resume_all (struct vmw_private*) ; 
 struct vmw_plane_state* vmw_plane_state_to_vps (struct drm_plane_state*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_svga_enable (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_vram_ne_placement ; 

__attribute__((used)) static int
vmw_sou_primary_plane_prepare_fb(struct drm_plane *plane,
				 struct drm_plane_state *new_state)
{
	struct drm_framebuffer *new_fb = new_state->fb;
	struct drm_crtc *crtc = plane->state->crtc ?: new_state->crtc;
	struct vmw_plane_state *vps = vmw_plane_state_to_vps(new_state);
	struct vmw_private *dev_priv;
	size_t size;
	int ret;


	if (!new_fb) {
		vmw_bo_unreference(&vps->bo);
		vps->bo_size = 0;

		return 0;
	}

	size = new_state->crtc_w * new_state->crtc_h * 4;
	dev_priv = vmw_priv(crtc->dev);

	if (vps->bo) {
		if (vps->bo_size == size) {
			/*
			 * Note that this might temporarily up the pin-count
			 * to 2, until cleanup_fb() is called.
			 */
			return vmw_bo_pin_in_vram(dev_priv, vps->bo,
						      true);
		}

		vmw_bo_unreference(&vps->bo);
		vps->bo_size = 0;
	}

	vps->bo = kzalloc(sizeof(*vps->bo), GFP_KERNEL);
	if (!vps->bo)
		return -ENOMEM;

	vmw_svga_enable(dev_priv);

	/* After we have alloced the backing store might not be able to
	 * resume the overlays, this is preferred to failing to alloc.
	 */
	vmw_overlay_pause_all(dev_priv);
	ret = vmw_bo_init(dev_priv, vps->bo, size,
			      &vmw_vram_ne_placement,
			      false, &vmw_bo_bo_free);
	vmw_overlay_resume_all(dev_priv);
	if (ret) {
		vps->bo = NULL; /* vmw_bo_init frees on error */
		return ret;
	}

	vps->bo_size = size;

	/*
	 * TTM already thinks the buffer is pinned, but make sure the
	 * pin_count is upped.
	 */
	return vmw_bo_pin_in_vram(dev_priv, vps->bo, true);
}