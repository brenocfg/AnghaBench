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
struct vmw_private {int /*<<< orphan*/  dev; } ;
struct vmw_fb_par {int /*<<< orphan*/  bo_mutex; struct drm_display_mode* set_mode; int /*<<< orphan*/  local_work; TYPE_1__* set_fb; int /*<<< orphan*/  fb_y; int /*<<< orphan*/  fb_x; int /*<<< orphan*/  con; int /*<<< orphan*/  crtc; struct vmw_private* vmw_priv; } ;
struct fb_var_screeninfo {int xres; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres; } ;
struct fb_info {struct fb_var_screeninfo var; struct vmw_fb_par* par; } ;
struct drm_mode_set {int num_connectors; int /*<<< orphan*/ * connectors; TYPE_1__* fb; struct drm_display_mode* mode; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  crtc; } ;
struct drm_display_mode {int hdisplay; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_DRIVER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  drm_mode_destroy (int /*<<< orphan*/ ,struct drm_display_mode*) ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,struct drm_display_mode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fb_dirty_mark (struct vmw_fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmw_fb_kms_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  vmw_guess_mode_timing (struct drm_display_mode*) ; 
 int /*<<< orphan*/  vmw_kms_validate_mode_vram (struct vmw_private*,int,int /*<<< orphan*/ ) ; 
 int vmwgfx_set_config_internal (struct drm_mode_set*) ; 

__attribute__((used)) static int vmw_fb_set_par(struct fb_info *info)
{
	struct vmw_fb_par *par = info->par;
	struct vmw_private *vmw_priv = par->vmw_priv;
	struct drm_mode_set set;
	struct fb_var_screeninfo *var = &info->var;
	struct drm_display_mode new_mode = { DRM_MODE("fb_mode",
		DRM_MODE_TYPE_DRIVER,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
	};
	struct drm_display_mode *mode;
	int ret;

	mode = drm_mode_duplicate(vmw_priv->dev, &new_mode);
	if (!mode) {
		DRM_ERROR("Could not create new fb mode.\n");
		return -ENOMEM;
	}

	mode->hdisplay = var->xres;
	mode->vdisplay = var->yres;
	vmw_guess_mode_timing(mode);

	if (!vmw_kms_validate_mode_vram(vmw_priv,
					mode->hdisplay *
					DIV_ROUND_UP(var->bits_per_pixel, 8),
					mode->vdisplay)) {
		drm_mode_destroy(vmw_priv->dev, mode);
		return -EINVAL;
	}

	mutex_lock(&par->bo_mutex);
	ret = vmw_fb_kms_framebuffer(info);
	if (ret)
		goto out_unlock;

	par->fb_x = var->xoffset;
	par->fb_y = var->yoffset;

	set.crtc = par->crtc;
	set.x = 0;
	set.y = 0;
	set.mode = mode;
	set.fb = par->set_fb;
	set.num_connectors = 1;
	set.connectors = &par->con;

	ret = vmwgfx_set_config_internal(&set);
	if (ret)
		goto out_unlock;

	vmw_fb_dirty_mark(par, par->fb_x, par->fb_y,
			  par->set_fb->width, par->set_fb->height);

	/* If there already was stuff dirty we wont
	 * schedule a new work, so lets do it now */

	schedule_delayed_work(&par->local_work, 0);

out_unlock:
	if (par->set_mode)
		drm_mode_destroy(vmw_priv->dev, par->set_mode);
	par->set_mode = mode;

	mutex_unlock(&par->bo_mutex);

	return ret;
}