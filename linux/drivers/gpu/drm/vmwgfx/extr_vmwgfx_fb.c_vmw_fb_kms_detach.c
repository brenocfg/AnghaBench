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
struct vmw_fb_par {scalar_t__ vmw_bo; struct drm_framebuffer* set_fb; int /*<<< orphan*/ * set_mode; TYPE_1__* vmw_priv; int /*<<< orphan*/  con; int /*<<< orphan*/  crtc; } ;
struct drm_mode_set {int /*<<< orphan*/ * connectors; scalar_t__ num_connectors; int /*<<< orphan*/ * fb; int /*<<< orphan*/ * mode; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  crtc; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  drm_framebuffer_put (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_mode_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_unreference (scalar_t__*) ; 
 int vmwgfx_set_config_internal (struct drm_mode_set*) ; 

__attribute__((used)) static int vmw_fb_kms_detach(struct vmw_fb_par *par,
			     bool detach_bo,
			     bool unref_bo)
{
	struct drm_framebuffer *cur_fb = par->set_fb;
	int ret;

	/* Detach the KMS framebuffer from crtcs */
	if (par->set_mode) {
		struct drm_mode_set set;

		set.crtc = par->crtc;
		set.x = 0;
		set.y = 0;
		set.mode = NULL;
		set.fb = NULL;
		set.num_connectors = 0;
		set.connectors = &par->con;
		ret = vmwgfx_set_config_internal(&set);
		if (ret) {
			DRM_ERROR("Could not unset a mode.\n");
			return ret;
		}
		drm_mode_destroy(par->vmw_priv->dev, par->set_mode);
		par->set_mode = NULL;
	}

	if (cur_fb) {
		drm_framebuffer_put(cur_fb);
		par->set_fb = NULL;
	}

	if (par->vmw_bo && detach_bo && unref_bo)
		vmw_bo_unreference(&par->vmw_bo);

	return 0;
}