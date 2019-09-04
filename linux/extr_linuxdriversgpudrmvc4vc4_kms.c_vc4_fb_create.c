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
struct vc4_bo {scalar_t__ t_format; } ;
struct drm_mode_fb_cmd2 {int flags; int /*<<< orphan*/ * modifier; int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED ; 
 int /*<<< orphan*/  DRM_FORMAT_MOD_NONE ; 
 int DRM_MODE_FB_MODIFIERS ; 
 int /*<<< orphan*/  ENOENT ; 
 struct drm_framebuffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct drm_framebuffer* drm_gem_fb_create (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2 const*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 

__attribute__((used)) static struct drm_framebuffer *vc4_fb_create(struct drm_device *dev,
					     struct drm_file *file_priv,
					     const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_mode_fb_cmd2 mode_cmd_local;

	/* If the user didn't specify a modifier, use the
	 * vc4_set_tiling_ioctl() state for the BO.
	 */
	if (!(mode_cmd->flags & DRM_MODE_FB_MODIFIERS)) {
		struct drm_gem_object *gem_obj;
		struct vc4_bo *bo;

		gem_obj = drm_gem_object_lookup(file_priv,
						mode_cmd->handles[0]);
		if (!gem_obj) {
			DRM_DEBUG("Failed to look up GEM BO %d\n",
				  mode_cmd->handles[0]);
			return ERR_PTR(-ENOENT);
		}
		bo = to_vc4_bo(gem_obj);

		mode_cmd_local = *mode_cmd;

		if (bo->t_format) {
			mode_cmd_local.modifier[0] =
				DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED;
		} else {
			mode_cmd_local.modifier[0] = DRM_FORMAT_MOD_NONE;
		}

		drm_gem_object_put_unlocked(gem_obj);

		mode_cmd = &mode_cmd_local;
	}

	return drm_gem_fb_create(dev, file_priv, mode_cmd);
}